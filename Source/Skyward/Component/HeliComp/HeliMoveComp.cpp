// Fill out your copyright notice in the Description page of Project Settings.


#include "../../Component/HeliComp/HeliMoveComp.h"
#include <EnhancedInputComponent.h>
#include "../../Helicopter/Helicopter_Apache.h"
#include <ChaosVehicleMovementComponent.h>
#include <Kismet/KismetMathLibrary.h>
#include "HeliSoundComp.h"
#include <Kismet/KismetSystemLibrary.h>
#include <../../../../../../../Plugins/FX/Niagara/Source/Niagara/Public/NiagaraFunctionLibrary.h>
#include "../../Actor/Heliport.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include "../../GameModeBase/SkywardGameModeBase.h"

UHeliMoveComp::UHeliMoveComp()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UHeliMoveComp::BeginPlay()
{
	Super::BeginPlay();
	
	SkywardGM = Cast<ASkywardGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	DriveMode = EDriveMode::NOMALMODE;

	// 헬기 고도의 기준점 초기화
	StandHigh = Apache->GetActorLocation().Z;

}

void UHeliMoveComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bIsEngineOnOff == true) {

		if (DriveMode == EDriveMode::NOMALMODE) {
			// 일반 운행 모드 

			// 헬기 소리 호출
			if (HeliComp_Sound) {
				HeliComp_Sound->PlayHeliSound_Engine();
			}

			// 헬기 움직임 
			// MainRotorSpeedRate는 엔진을 키면 자동으로 올라감
			MainRotorSpeedRate = FMath::FInterpTo(MainRotorSpeedRate, 25.f, DeltaTime, 0.2f); // 최고속력 25

			// 애니메이션에서 사용 - 프로펠러 회전
			Apache->MainRotorSpeed_Apache += MainRotorSpeedRate;

			//MainRotorSpeedRate 가 일정 이상 올라가야 헬기가 움직일 수 있음
			if (MainRotorSpeedRate >= 15.f) {

				if (ActionValueUpDown == 0) {

					// 고도 유지 기능
					HoldHeliAltitude();

				}
				else
				{
					// 1이상 상승, -1이면 하강
					Apache->GetVehicleMovement()->SetThrottleInput(ActionValueUpDown);


				}

			}
		}
		/*
		else if (DriveMode == EDriveMode::AltitudeHoldMode) {
			// 고도 유지 모드



		}
		else if (DriveMode == EDriveMode::AutoHoveringMode) {
			// 자동 호버링 모드
			FVector HoveringLocation = Apache->GetActorLocation();

			//Apache->SetActorLocation(HoveringLocation);
		}
		*/

	}
	else { // 헬기 엔진 꺼짐
		// 헬기 소리 호출 - 시동끄는 소리
		if (HeliComp_Sound) {
			HeliComp_Sound->PlayHeliSound_Engine();
		}

		// 헬기 움직임
		MainRotorSpeedRate = FMath::FInterpTo(MainRotorSpeedRate, 0, DeltaTime, 1.f); // 최고속력 25

		// 애니메이션에서 사용 - 프로펠러 회전
		Apache->MainRotorSpeed_Apache += MainRotorSpeedRate;
	}



	/*
	// 헬기 각도 로그 -------------------------------------------------------
	CurrentPitch = Apache->GetActorRotation().Pitch;
	CurrentRoll = Apache->GetActorRotation().Roll;

	// 전후 수평 로그
	UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("VehicleMovementComponent Pitch: %f"), CurrentPitch), true, false, FLinearColor::Green, 5.0f, FName(TEXT("VehiclePitch")));
	// 좌우 수평 로그
	UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("VehicleMovementComponent Roll: %f"), CurrentRoll), true, false, FLinearColor::Green, 5.0f, FName(TEXT("VehicleRoll")));
	// 고도 - 절대좌표
	UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("ApacheAltitude: %f"), ApacheAltitude), true, false, FLinearColor::Green, 5.0f, FName(TEXT("StandHigh")));
	// 고도 - 헬기 기준 상대좌표
	UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("Apache->GetActorLocation().Z: %f"), Apache->GetActorLocation().Z - StandHigh), true, false, FLinearColor::Green, 5.0f, FName(TEXT("Apache->GetActorLocation().Z")));
	*/

}

void UHeliMoveComp::SetupPlayerInput(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInput(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	// VR 컨트롤러 바인딩
	if (EnhancedInputComponent) {

		// 헬기 엔진
		EnhancedInputComponent->BindAction(IA_Apache_Engine, ETriggerEvent::Started, this, &UHeliMoveComp::Engine_On_Off);

		// 헬기 방향(기울기)
		EnhancedInputComponent->BindAction(IA_Apache_Cyclic, ETriggerEvent::Triggered, this, &UHeliMoveComp::Cyclic_RightThumbStick);
		EnhancedInputComponent->BindAction(IA_Apache_Cyclic, ETriggerEvent::Canceled, this, &UHeliMoveComp::Cyclic_RightThumbStick);
		EnhancedInputComponent->BindAction(IA_Apache_Cyclic, ETriggerEvent::Completed, this, &UHeliMoveComp::Cyclic_RightThumbStick);

		// 헬기 고도
		EnhancedInputComponent->BindAction(IA_Apache_Collective, ETriggerEvent::Triggered, this, &UHeliMoveComp::Collective_LeftGrip);
		EnhancedInputComponent->BindAction(IA_Apache_Collective, ETriggerEvent::Canceled, this, &UHeliMoveComp::Collective_LeftGrip);
		EnhancedInputComponent->BindAction(IA_Apache_Collective, ETriggerEvent::Completed, this, &UHeliMoveComp::Collective_LeftGrip);

		// 헬기 회전
		EnhancedInputComponent->BindAction(IA_Apache_Pedal, ETriggerEvent::Triggered, this, &UHeliMoveComp::Pedal_Trigger);
		EnhancedInputComponent->BindAction(IA_Apache_Pedal, ETriggerEvent::Canceled, this, &UHeliMoveComp::Pedal_Trigger);
		EnhancedInputComponent->BindAction(IA_Apache_Pedal, ETriggerEvent::Completed, this, &UHeliMoveComp::Pedal_Trigger);

		EnhancedInputComponent->BindAction(IA_Apache_Throttle, ETriggerEvent::Triggered, this, &UHeliMoveComp::Pedal_Trigger); // 호출함수 수정 필요

		EnhancedInputComponent->BindAction(IA_Apache_DriveMode, ETriggerEvent::Started, this, &UHeliMoveComp::ChangeDrivingMode); // 호출함수 수정 필요

	}

}

void UHeliMoveComp::Engine_On_Off(const FInputActionValue& value)
{
	if (bIsEngineOnOff == false) {

		bIsEngineOnOff = true;

		// 바람 이펙트 
		if (NSWind) {

			UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), NSWind, Apache->GetActorLocation() - FVector(0, 0, 700), FRotator(0), FVector(5));
		}

		// 브레이크 끄기
		Apache->GetVehicleMovementComponent()->SetHandbrakeInput(false);

	}
	else if (bIsEngineOnOff == true) {

		// 지면과의 거리를 계산
		FHitResult hitResult;
		FVector startLoc = Apache->GetActorLocation() + FVector(0, 0, 50);
		FVector endLoc = Apache->GetActorLocation() + FVector(0, 0, -10);
		TArray<class AActor*> IngnoreActors;

		IngnoreActors.Add(Apache);
		FCollisionQueryParams CollisionParams;
		CollisionParams.AddIgnoredActors(IngnoreActors);

		// 지면과 가까운지를 감지하는 라인트레이스
		GetWorld()->LineTraceSingleByChannel(hitResult, startLoc, endLoc, ECC_Visibility, CollisionParams);

		//DrawDebugLine(GetWorld(), startLoc, endLoc, FColor::Red, false, 0, 0, 5);

		if (hitResult.bBlockingHit == true) {

			bIsEngineOnOff = false;

			Apache->GetVehicleMovementComponent()->SetHandbrakeInput(true);

			// 주차시 헬리포트 위에 있으면 미션 성공
			if (hitResult.GetActor()->IsA<AHeliport>()) {

				SkywardGM->bIsSuccess = true;

				// 위젯 여는 소리
				if (Apache->WinSound) {
					UGameplayStatics::PlaySound2D(GetWorld(), Apache->WinSound);
				}

			}

		}

	}

}

void UHeliMoveComp::ChangeDrivingMode(const FInputActionValue& value)
{
	/*
	if (DriveMode == EDriveMode::NOMALMODE) {
		DriveMode = EDriveMode::AltitudeHoldMode;

	}
	else if (DriveMode == EDriveMode::AltitudeHoldMode) {
		DriveMode = EDriveMode::AutoHoveringMode;

	}
	else if (DriveMode == EDriveMode::AltitudeHoldMode) {
		DriveMode = EDriveMode::NOMALMODE;

	}
	*/

}

EDriveMode UHeliMoveComp::GetDriveMode() const
{
	return EDriveMode();
}

// VR 컨트롤러 ==========================================================================

void UHeliMoveComp::Cyclic_RightThumbStick(const FInputActionValue& value)
{
	FVector2D VecterValue = value.Get<FVector2D>();

	if (VecterValue != FVector2D::ZeroVector) {
		// 입력에 따라 각도 조절

		if (FMath::Abs(VecterValue.Y) > FMath::Abs(VecterValue.X)) {
			Apache->AddControllerPitchInput(VecterValue.Y);
			Apache->GetVehicleMovementComponent()->SetPitchInput(VecterValue.Y);

		}
		else if (FMath::Abs(VecterValue.X) > FMath::Abs(VecterValue.Y)) {
			Apache->AddControllerRollInput(VecterValue.X);
			Apache->GetVehicleMovementComponent()->SetRollInput(VecterValue.X);

		}

	}
	else {
		// 입력이 없으면 각도 조절 멈춤
		StopUpdatingHelicopterAngle();
	}

	// ============================================================================================================
	/*
	if (VecterValue != FVector2D::ZeroVector) {
		// 입력에 따라 각도 조절

		float HeliDrectionAngle = 0;

		float CurrnetDrectionAngle = 0;
		float PreDrectionAngle = 0;


		if (FMath::Abs(VecterValue.Y) > FMath::Abs(VecterValue.X)) {

			// VecterValue.Y는 -1 ~ 1 사이의 값이다.
			// -1인 경우 뒤로 30도 , 1인 경우 앞으로 30도로 기울어야 한다. 그 사이 값은 스틱의 기울기에 비례하여 헬기가 기울어야 한다.
			// 하지만 SetPitchInput은 -1, 0, 1의 값으로만 움직일 수 있다.
			// 이전 입력 값과 현재 입력 값을 비교하면 되지 않을까?
			// 이전 입력값보다 현재 입력 값이 크면 각도를 1을 반환하여 크게 갱신 / 동일하면 0을 반환하여 유지 / 작으면 -1을 반환하여 작게 갱신



			CurrnetDrectionAngle = VecterValue.Y;


			if (CurrnetDrectionAngle > PreDrectionAngle) {
				HeliDrectionAngle = 1;
			}
			else if (CurrnetDrectionAngle < PreDrectionAngle) {
				HeliDrectionAngle = -1;
			}
			else {
				HeliDrectionAngle = 0;

			}

			Apache->AddControllerPitchInput(HeliDrectionAngle);
			Apache->GetVehicleMovementComponent()->SetPitchInput(HeliDrectionAngle);

			PreDrectionAngle = CurrnetDrectionAngle;

			// ==============================

			HeliDrectionAngle = FMath::Clamp(VecterValue.Y * 30, -30, 30);

			Apache->SetActorRotation(FRotator(HeliDrectionAngle, 0, 0));

		}
		else if (FMath::Abs(VecterValue.X) > FMath::Abs(VecterValue.Y)) {



			HeliDrectionAngle = VecterValue.X;

			Apache->AddControllerRollInput(VecterValue.X);
			Apache->GetVehicleMovementComponent()->SetRollInput(VecterValue.X);

		}

	}
	else {
		// 입력이 없으면 각도 조절 멈춤
		StopUpdatingHelicopterAngle();


	}
	*/

	//UKismetSystemLibrary::PrintString(this, VecterValue.ToString(), true, false, FLinearColor::Green, 5.0f, FName(TEXT("VecterValue")));

}

void UHeliMoveComp::UpdateHelicopterAngle(const FVector2D& InputValue)
{
	// **************** 현재 이 코드 안쓰는 중

	// 입력에 따라 헬기의 각도 조절
	float PitchAngle = FMath::Clamp(InputValue.Y * 30.f, -30.f, 30.f);
	float RollAngle = FMath::Clamp(InputValue.X * 30.f, -30.f, 30.f);


	Apache->AddControllerPitchInput(PitchAngle);
	Apache->GetVehicleMovementComponent()->SetPitchInput(PitchAngle);

	Apache->AddControllerRollInput(RollAngle);
	Apache->GetVehicleMovementComponent()->SetRollInput(RollAngle);

}

void UHeliMoveComp::StopUpdatingHelicopterAngle()
{
	// 헬기의 각도 조절 멈춤
	Apache->AddControllerPitchInput(0.0f);
	Apache->GetVehicleMovementComponent()->SetPitchInput(0.0f);

	Apache->AddControllerRollInput(0.0f);
	Apache->GetVehicleMovementComponent()->SetRollInput(0.0f);

}

void UHeliMoveComp::Collective_LeftGrip(const FInputActionValue& value)
{
	// 헬기의 고도를 조종

	// ================================================================

	//ActionValueUpDown = value.Get<float>();

	// ================================================================
	if (value.Get<float>() == 0) {
		ActionValueUpDown = -1;

		ApacheAltitude = Apache->GetActorLocation().Z;

	}
	else if (value.Get<float>() == 1) {
		ActionValueUpDown = 1;

		ApacheAltitude = Apache->GetActorLocation().Z;

	}
	else {
		ActionValueUpDown = 0;

		// ApacheAltitude 의 값이 하나로 설정되어야 고도를 유지할 수 있는데, 현재 trigger 상태라 계속해서 ApacheAltitude가 갱신되므로 고도를 유지하지 않고 계속 상승함
		//ApacheAltitude = Apache->GetActorLocation().Z;

	}

	// ================================================================

	/*
	// 고도를 6단계로 나눔
	if (value.Get<float>() == 0) {
		ActionValueUpDown = -1;

	}
	else if (value.Get<float>() == 1) {
		ActionValueUpDown = 1;
	}
	else {
		ActionValueUpDown = 0;

		if (value.Get<float>() <= 0.2f) {
			ApacheAltitude = StandHigh + MaxAltitude * 0.2f;

		}
		else if (value.Get<float>() <= 0.4f) {
			ApacheAltitude = StandHigh + MaxAltitude * 0.4f;

		}
		else if (value.Get<float>() <= 0.6f) {
			ApacheAltitude = StandHigh + MaxAltitude * 0.6f;

		}
		else if (value.Get<float>() <= 0.8f) {
			ApacheAltitude = StandHigh + MaxAltitude * 0.8f;

		}
		else {
			ApacheAltitude = StandHigh + MaxAltitude; // 최대 40000만

		}
	}
	*/

}

void UHeliMoveComp::Pedal_Trigger(const FInputActionValue& value)
{
	float YawValue = value.Get<float>();

	Apache->AddControllerYawInput(YawValue);

	Apache->GetVehicleMovementComponent()->SetYawInput(YawValue);
}

// VR 컨트롤러 ==========================================================================

void UHeliMoveComp::HoldHeliAltitude()
{
	// 헬기 고도를 유지하는 기능 

	if (MaxAltitude < ApacheAltitude) {
		ApacheAltitude = MaxAltitude;
	}

	// Out Range A 부분을 바꾸어 유지 고도를 바꿀 수 있음 -> 너무 크면 흔들림이 심하고, 너무 작으면 헬기가 추락함
	float Altitude = UKismetMathLibrary::MapRangeClamped(Apache->GetActorLocation().Z - ApacheAltitude, 0.f, 10.f, 0.7f, 0.f);

	Apache->GetVehicleMovement()->SetThrottleInput(Altitude);

	/*
	// 고도 유지 기능
	double CompPlayerAltitude = (Apache->GetActorLocation().Z - PlayerAltitude); // 현재 플레이어의 고도를 가져옴
	float MappedAltitude = UKismetMathLibrary::MapRangeClamped(CompPlayerAltitude, 0.f, 10.f, 0.7f, 0.f);
	*/
}
