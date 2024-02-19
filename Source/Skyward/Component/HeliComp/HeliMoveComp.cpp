// Fill out your copyright notice in the Description page of Project Settings.


#include "../../Component/HeliComp/HeliMoveComp.h"
#include <EnhancedInputComponent.h>
#include "../../Helicopter/Helicopter_Apache.h"
#include <ChaosVehicleMovementComponent.h>
#include <Kismet/KismetMathLibrary.h>
#include "HeliSoundComp.h"
#include <Kismet/KismetSystemLibrary.h>

UHeliMoveComp::UHeliMoveComp()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UHeliMoveComp::BeginPlay()
{
	Super::BeginPlay();

}

void UHeliMoveComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bIsEngineOnOff == true) {

		// 헬기 소리 호출
		if (HeliComp_Sound) {
			HeliComp_Sound->PlayHeliSound_Engine();
		}

		// 헬기 움직임 
		MainRotorSpeedRate = FMath::FInterpTo(MainRotorSpeedRate, 25.f, DeltaTime, 0.2f); // 최고속력 25

		// 애니메이션에서 사용 - 프로펠러 회전
		Apache->MainRotorSpeed += MainRotorSpeedRate;

		// MainRotorSpeedRate는 엔진을 키면 자동으로 올라감
		if (MainRotorSpeedRate >= 15.f) {

			if (ActionValueUpDown == 0) {

				// 고도 유지 기능
				HoldHeliAltitude();

			}
			else
			{
				Apache->GetVehicleMovement()->SetThrottleInput(ActionValueUpDown);
			}

		}

	}
	else { // 헬기 엔진 꺼짐
		// 헬기 소리 호출 - 시동끄는 소리
		if (HeliComp_Sound) {
			HeliComp_Sound->PlayHeliSound_Engine();
		}

		// 헬기 움직임
		MainRotorSpeedRate = FMath::FInterpTo(MainRotorSpeedRate, 0, DeltaTime, 1.f); // 최고속력 25

		// 애니메이션에서 사용 - 프로펠러 회전
		Apache->MainRotorSpeed += MainRotorSpeedRate;
	}





	// 헬기 각도 로그 -------------------------------------------------------
	CurrentPitch = Apache->GetActorRotation().Pitch;
	CurrentRoll = Apache->GetActorRotation().Roll;


	UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("VehicleMovementComponent Pitch: %f"), CurrentPitch), true, false, FLinearColor::Green, 5.0f, FName(TEXT("VehiclePitch")));
	UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("VehicleMovementComponent Roll: %f"), CurrentRoll), true, false, FLinearColor::Green, 5.0f, FName(TEXT("VehicleRoll")));

}

void UHeliMoveComp::SetupPlayerInput(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInput(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	// VR 컨트롤러 바인딩
	if (EnhancedInputComponent) {
		
		// 헬기 방향(기울기)
		EnhancedInputComponent->BindAction(IA_Apache_Cyclic, ETriggerEvent::Triggered, this, &UHeliMoveComp::Cyclie_RightThumbStick);
		EnhancedInputComponent->BindAction(IA_Apache_Cyclic, ETriggerEvent::Canceled, this, &UHeliMoveComp::Cyclie_RightThumbStick);
		EnhancedInputComponent->BindAction(IA_Apache_Cyclic, ETriggerEvent::Completed, this, &UHeliMoveComp::Cyclie_RightThumbStick);

		// 헬기 고도
		EnhancedInputComponent->BindAction(IA_Apache_Collective, ETriggerEvent::Triggered, this, &UHeliMoveComp::Collective_LeftGrip);
		EnhancedInputComponent->BindAction(IA_Apache_Collective, ETriggerEvent::Canceled, this, &UHeliMoveComp::Collective_LeftGrip);
		EnhancedInputComponent->BindAction(IA_Apache_Collective, ETriggerEvent::Completed, this, &UHeliMoveComp::Collective_LeftGrip);

		// 헬기 회전
		EnhancedInputComponent->BindAction(IA_Apache_Pedal, ETriggerEvent::Triggered, this, &UHeliMoveComp::Pedal_Trigger);
		EnhancedInputComponent->BindAction(IA_Apache_Pedal, ETriggerEvent::Canceled, this, &UHeliMoveComp::Pedal_Trigger);
		EnhancedInputComponent->BindAction(IA_Apache_Pedal, ETriggerEvent::Completed, this, &UHeliMoveComp::Pedal_Trigger);

	}

}

void UHeliMoveComp::On_Off_Function(const FInputActionValue& value)
{
	if (bIsEngineOnOff == false) {

		bIsEngineOnOff = true;

		Apache->GetVehicleMovementComponent()->SetHandbrakeInput(false);

	}
	else if (bIsEngineOnOff == true) {

		FHitResult hitResult;
		FVector startLoc = Apache->GetActorLocation() + FVector(0, 0, 50);
		FVector endLoc = Apache->GetActorLocation() + FVector(0, 0, -10);
		TArray<class AActor*> IngnoreActors;

		IngnoreActors.Add(Apache);
		FCollisionQueryParams CollisionParams;
		CollisionParams.AddIgnoredActors(IngnoreActors);

		// 지면과 가까운지를 감지하는 라인트레이스
		GetWorld()->LineTraceSingleByChannel(hitResult, startLoc, endLoc, ECC_Visibility, CollisionParams);

		DrawDebugLine(GetWorld(), startLoc, endLoc, FColor::Red, false, 0, 0, 5);

		if (hitResult.bBlockingHit == true) {

			bIsEngineOnOff = false;

			Apache->GetVehicleMovementComponent()->SetHandbrakeInput(true);

		}

	}

}

// VR 컨트롤러 ==========================================================================

void UHeliMoveComp::Cyclie_RightThumbStick(const FInputActionValue& value)
{
	FVector2D VecterValue = value.Get<FVector2D>();

	//UKismetSystemLibrary::PrintString(const UObject * WorldContextObject, const FString & InString, bool bPrintToScreen, bool bPrintToLog, FLinearColor TextColor, float Duration, const FName Key)

	UKismetSystemLibrary::PrintString(this, VecterValue.ToString(), true, false, FLinearColor::Green, 5.0f, FName(TEXT("VecterValue")));

	/*
	// 이대로 하면 썸스틱을 더 입력하지 않아도 헬기가 계속 회전함

	// 전진, 후퇴
	if (VecterValue.Y != 0) {

		Apache->AddControllerPitchInput(VecterValue.Y);

		Apache->GetVehicleMovementComponent()->SetPitchInput(VecterValue.Y);

	}

	// 오른쪽, 왼쪽
	if (VecterValue.X != 0) {
		Apache->AddControllerRollInput(VecterValue.X);

		Apache->GetVehicleMovementComponent()->SetRollInput(VecterValue.X);

	}
	*/


	// 썸 스틱의 기울여진 각도에 비례하여 헬기의 몸체가 기울여져야 함.(각도에 따라 0 ~ 1 사이의 값을 float로 반환함)
	// 최대 각도 30도
	// 조작의 편의성을 위해 스틱의 민간도를 조절할 필요가 있음 -> 입력 값이 0.5 이상일 때부터 0 ~ 30도 사이로 기울여짐
	// 혹은 한 쪽의 입력의 절댓값이 다른 입력보다 크면, 큰 쪽으로 기울여짐


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


	/*
	if (VecterValue != FVector2D::ZeroVector) {
		// 입력에 따라 각도 조절

		if (FMath::Abs(VecterValue.Y) > FMath::Abs(VecterValue.X)) {

			if (FMath::Abs(Apache->GetActorRotation().Pitch) < 30.f) {
				//Apache->AddControllerPitchInput(VecterValue.Y);
				//Apache->GetVehicleMovementComponent()->SetPitchInput(VecterValue.Y);

			}
			else if (FMath::Abs(Apache->GetActorRotation().Pitch) > 30.f) {
				StopUpdatingHelicopterAngle();

			}

		}
		else if (FMath::Abs(VecterValue.X) > FMath::Abs(VecterValue.Y)) {

			if (FMath::Abs(Apache->GetActorRotation().Roll) < 30.f) {
				Apache->AddControllerRollInput(VecterValue.X);
				Apache->GetVehicleMovementComponent()->SetRollInput(VecterValue.X);


			}
			else if (FMath::Abs(Apache->GetActorRotation().Roll) > 30.f) {
				StopUpdatingHelicopterAngle();

		}
	}
	else {
		// 입력이 없으면 각도 조절 멈춤
		StopUpdatingHelicopterAngle();
	}
	*/


	/*
	// 입력값이 0이 아닌 경우에만 각도 조절
	if (VecterValue != FVector2D::ZeroVector) {
		// 입력에 따라 각도 조절
		UpdateHelicopterAngle(VecterValue);
	}
	else {
		// 입력이 없으면 각도 조절 멈춤
		StopUpdatingHelicopterAngle();
	}
	*/


}

void UHeliMoveComp::UpdateHelicopterAngle(const FVector2D& InputValue)
{
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
	// value값에 따라 하강, 유지, 상승로 헬기의 고도를 조절
	// 왼손 그랩의 반환 값에 따라 단계를 0~4로 나누고, 각 단계에 따라 고도가 달라진다. - 최대 7000m



	UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("ActionValueUpDown: %f"), ActionValueUpDown), true, false, FLinearColor::Green, 5.0f, FName(TEXT("ActionValueLog")));


	ActionValueUpDown = value.Get<float>();

	/*
	float YawValue = value.Get<float>();
	
	if (YawValue == 0) {

		ActionValueUpDown = -1;
	
	}
	else if (0 < YawValue && YawValue < 1) {
	
		ActionValueUpDown = 0;

	}
	else if (YawValue == 1) {

		ActionValueUpDown = 1;

	}
	*/

	
	if (ActionValueUpDown == 0) {

		ApacheAltitude = Apache->GetActorLocation().Z;
		// -> 0일 때는 고도 유지, 현재고도 보다 낮을 때는 하강, 높을 때는 상승, 1일 때는 상승하도록 작동 중 
	}

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
	
	// Out Range A 부분을 바꾸어 유지 고도를 바꿀 수 있음 -> 너무 크면 흔들림이 심하고, 너무 작으면 헬기가 추락함
	float Altitude = UKismetMathLibrary::MapRangeClamped(Apache->GetActorLocation().Z - ApacheAltitude, 0.f, 10.f, 0.7f, 0.f);

	Apache->GetVehicleMovement()->SetThrottleInput(Altitude);


	/*
	// 고도 유지 기능
	double CompPlayerAltitude = (Apache->GetActorLocation().Z - PlayerAltitude); // 현재 플레이어의 고도를 가져옴
	float MappedAltitude = UKismetMathLibrary::MapRangeClamped(CompPlayerAltitude, 0.f, 10.f, 0.7f, 0.f);
	*/
}
