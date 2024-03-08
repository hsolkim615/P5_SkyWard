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

	// ��� ���� ������ �ʱ�ȭ
	StandHigh = Apache->GetActorLocation().Z;

}

void UHeliMoveComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bIsEngineOnOff == true) {

		if (DriveMode == EDriveMode::NOMALMODE) {
			// �Ϲ� ���� ��� 

			// ��� �Ҹ� ȣ��
			if (HeliComp_Sound) {
				HeliComp_Sound->PlayHeliSound_Engine();
			}

			// ��� ������ 
			// MainRotorSpeedRate�� ������ Ű�� �ڵ����� �ö�
			MainRotorSpeedRate = FMath::FInterpTo(MainRotorSpeedRate, 25.f, DeltaTime, 0.2f); // �ְ�ӷ� 25

			// �ִϸ��̼ǿ��� ��� - �����緯 ȸ��
			Apache->MainRotorSpeed_Apache += MainRotorSpeedRate;

			//MainRotorSpeedRate �� ���� �̻� �ö󰡾� ��Ⱑ ������ �� ����
			if (MainRotorSpeedRate >= 15.f) {

				if (ActionValueUpDown == 0) {

					// �� ���� ���
					HoldHeliAltitude();

				}
				else
				{
					// 1�̻� ���, -1�̸� �ϰ�
					Apache->GetVehicleMovement()->SetThrottleInput(ActionValueUpDown);


				}

			}
		}
		/*
		else if (DriveMode == EDriveMode::AltitudeHoldMode) {
			// �� ���� ���



		}
		else if (DriveMode == EDriveMode::AutoHoveringMode) {
			// �ڵ� ȣ���� ���
			FVector HoveringLocation = Apache->GetActorLocation();

			//Apache->SetActorLocation(HoveringLocation);
		}
		*/

	}
	else { // ��� ���� ����
		// ��� �Ҹ� ȣ�� - �õ����� �Ҹ�
		if (HeliComp_Sound) {
			HeliComp_Sound->PlayHeliSound_Engine();
		}

		// ��� ������
		MainRotorSpeedRate = FMath::FInterpTo(MainRotorSpeedRate, 0, DeltaTime, 1.f); // �ְ�ӷ� 25

		// �ִϸ��̼ǿ��� ��� - �����緯 ȸ��
		Apache->MainRotorSpeed_Apache += MainRotorSpeedRate;
	}



	/*
	// ��� ���� �α� -------------------------------------------------------
	CurrentPitch = Apache->GetActorRotation().Pitch;
	CurrentRoll = Apache->GetActorRotation().Roll;

	// ���� ���� �α�
	UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("VehicleMovementComponent Pitch: %f"), CurrentPitch), true, false, FLinearColor::Green, 5.0f, FName(TEXT("VehiclePitch")));
	// �¿� ���� �α�
	UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("VehicleMovementComponent Roll: %f"), CurrentRoll), true, false, FLinearColor::Green, 5.0f, FName(TEXT("VehicleRoll")));
	// �� - ������ǥ
	UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("ApacheAltitude: %f"), ApacheAltitude), true, false, FLinearColor::Green, 5.0f, FName(TEXT("StandHigh")));
	// �� - ��� ���� �����ǥ
	UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("Apache->GetActorLocation().Z: %f"), Apache->GetActorLocation().Z - StandHigh), true, false, FLinearColor::Green, 5.0f, FName(TEXT("Apache->GetActorLocation().Z")));
	*/

}

void UHeliMoveComp::SetupPlayerInput(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInput(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	// VR ��Ʈ�ѷ� ���ε�
	if (EnhancedInputComponent) {

		// ��� ����
		EnhancedInputComponent->BindAction(IA_Apache_Engine, ETriggerEvent::Started, this, &UHeliMoveComp::Engine_On_Off);

		// ��� ����(����)
		EnhancedInputComponent->BindAction(IA_Apache_Cyclic, ETriggerEvent::Triggered, this, &UHeliMoveComp::Cyclic_RightThumbStick);
		EnhancedInputComponent->BindAction(IA_Apache_Cyclic, ETriggerEvent::Canceled, this, &UHeliMoveComp::Cyclic_RightThumbStick);
		EnhancedInputComponent->BindAction(IA_Apache_Cyclic, ETriggerEvent::Completed, this, &UHeliMoveComp::Cyclic_RightThumbStick);

		// ��� ��
		EnhancedInputComponent->BindAction(IA_Apache_Collective, ETriggerEvent::Triggered, this, &UHeliMoveComp::Collective_LeftGrip);
		EnhancedInputComponent->BindAction(IA_Apache_Collective, ETriggerEvent::Canceled, this, &UHeliMoveComp::Collective_LeftGrip);
		EnhancedInputComponent->BindAction(IA_Apache_Collective, ETriggerEvent::Completed, this, &UHeliMoveComp::Collective_LeftGrip);

		// ��� ȸ��
		EnhancedInputComponent->BindAction(IA_Apache_Pedal, ETriggerEvent::Triggered, this, &UHeliMoveComp::Pedal_Trigger);
		EnhancedInputComponent->BindAction(IA_Apache_Pedal, ETriggerEvent::Canceled, this, &UHeliMoveComp::Pedal_Trigger);
		EnhancedInputComponent->BindAction(IA_Apache_Pedal, ETriggerEvent::Completed, this, &UHeliMoveComp::Pedal_Trigger);

		EnhancedInputComponent->BindAction(IA_Apache_Throttle, ETriggerEvent::Triggered, this, &UHeliMoveComp::Pedal_Trigger); // ȣ���Լ� ���� �ʿ�

		EnhancedInputComponent->BindAction(IA_Apache_DriveMode, ETriggerEvent::Started, this, &UHeliMoveComp::ChangeDrivingMode); // ȣ���Լ� ���� �ʿ�

	}

}

void UHeliMoveComp::Engine_On_Off(const FInputActionValue& value)
{
	if (bIsEngineOnOff == false) {

		bIsEngineOnOff = true;

		// �ٶ� ����Ʈ 
		if (NSWind) {

			UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), NSWind, Apache->GetActorLocation() - FVector(0, 0, 700), FRotator(0), FVector(5));
		}

		// �극��ũ ����
		Apache->GetVehicleMovementComponent()->SetHandbrakeInput(false);

	}
	else if (bIsEngineOnOff == true) {

		// ������� �Ÿ��� ���
		FHitResult hitResult;
		FVector startLoc = Apache->GetActorLocation() + FVector(0, 0, 50);
		FVector endLoc = Apache->GetActorLocation() + FVector(0, 0, -10);
		TArray<class AActor*> IngnoreActors;

		IngnoreActors.Add(Apache);
		FCollisionQueryParams CollisionParams;
		CollisionParams.AddIgnoredActors(IngnoreActors);

		// ����� ��������� �����ϴ� ����Ʈ���̽�
		GetWorld()->LineTraceSingleByChannel(hitResult, startLoc, endLoc, ECC_Visibility, CollisionParams);

		//DrawDebugLine(GetWorld(), startLoc, endLoc, FColor::Red, false, 0, 0, 5);

		if (hitResult.bBlockingHit == true) {

			bIsEngineOnOff = false;

			Apache->GetVehicleMovementComponent()->SetHandbrakeInput(true);

			// ������ �︮��Ʈ ���� ������ �̼� ����
			if (hitResult.GetActor()->IsA<AHeliport>()) {

				SkywardGM->bIsSuccess = true;

				// ���� ���� �Ҹ�
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

// VR ��Ʈ�ѷ� ==========================================================================

void UHeliMoveComp::Cyclic_RightThumbStick(const FInputActionValue& value)
{
	FVector2D VecterValue = value.Get<FVector2D>();

	if (VecterValue != FVector2D::ZeroVector) {
		// �Է¿� ���� ���� ����

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
		// �Է��� ������ ���� ���� ����
		StopUpdatingHelicopterAngle();
	}

	// ============================================================================================================
	/*
	if (VecterValue != FVector2D::ZeroVector) {
		// �Է¿� ���� ���� ����

		float HeliDrectionAngle = 0;

		float CurrnetDrectionAngle = 0;
		float PreDrectionAngle = 0;


		if (FMath::Abs(VecterValue.Y) > FMath::Abs(VecterValue.X)) {

			// VecterValue.Y�� -1 ~ 1 ������ ���̴�.
			// -1�� ��� �ڷ� 30�� , 1�� ��� ������ 30���� ����� �Ѵ�. �� ���� ���� ��ƽ�� ���⿡ ����Ͽ� ��Ⱑ ����� �Ѵ�.
			// ������ SetPitchInput�� -1, 0, 1�� �����θ� ������ �� �ִ�.
			// ���� �Է� ���� ���� �Է� ���� ���ϸ� ���� ������?
			// ���� �Է°����� ���� �Է� ���� ũ�� ������ 1�� ��ȯ�Ͽ� ũ�� ���� / �����ϸ� 0�� ��ȯ�Ͽ� ���� / ������ -1�� ��ȯ�Ͽ� �۰� ����



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
		// �Է��� ������ ���� ���� ����
		StopUpdatingHelicopterAngle();


	}
	*/

	//UKismetSystemLibrary::PrintString(this, VecterValue.ToString(), true, false, FLinearColor::Green, 5.0f, FName(TEXT("VecterValue")));

}

void UHeliMoveComp::UpdateHelicopterAngle(const FVector2D& InputValue)
{
	// **************** ���� �� �ڵ� �Ⱦ��� ��

	// �Է¿� ���� ����� ���� ����
	float PitchAngle = FMath::Clamp(InputValue.Y * 30.f, -30.f, 30.f);
	float RollAngle = FMath::Clamp(InputValue.X * 30.f, -30.f, 30.f);


	Apache->AddControllerPitchInput(PitchAngle);
	Apache->GetVehicleMovementComponent()->SetPitchInput(PitchAngle);

	Apache->AddControllerRollInput(RollAngle);
	Apache->GetVehicleMovementComponent()->SetRollInput(RollAngle);

}

void UHeliMoveComp::StopUpdatingHelicopterAngle()
{
	// ����� ���� ���� ����
	Apache->AddControllerPitchInput(0.0f);
	Apache->GetVehicleMovementComponent()->SetPitchInput(0.0f);

	Apache->AddControllerRollInput(0.0f);
	Apache->GetVehicleMovementComponent()->SetRollInput(0.0f);

}

void UHeliMoveComp::Collective_LeftGrip(const FInputActionValue& value)
{
	// ����� ���� ����

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

		// ApacheAltitude �� ���� �ϳ��� �����Ǿ�� ���� ������ �� �ִµ�, ���� trigger ���¶� ����ؼ� ApacheAltitude�� ���ŵǹǷ� ���� �������� �ʰ� ��� �����
		//ApacheAltitude = Apache->GetActorLocation().Z;

	}

	// ================================================================

	/*
	// ���� 6�ܰ�� ����
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
			ApacheAltitude = StandHigh + MaxAltitude; // �ִ� 40000��

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

// VR ��Ʈ�ѷ� ==========================================================================

void UHeliMoveComp::HoldHeliAltitude()
{
	// ��� ���� �����ϴ� ��� 

	if (MaxAltitude < ApacheAltitude) {
		ApacheAltitude = MaxAltitude;
	}

	// Out Range A �κ��� �ٲپ� ���� ���� �ٲ� �� ���� -> �ʹ� ũ�� ��鸲�� ���ϰ�, �ʹ� ������ ��Ⱑ �߶���
	float Altitude = UKismetMathLibrary::MapRangeClamped(Apache->GetActorLocation().Z - ApacheAltitude, 0.f, 10.f, 0.7f, 0.f);

	Apache->GetVehicleMovement()->SetThrottleInput(Altitude);

	/*
	// �� ���� ���
	double CompPlayerAltitude = (Apache->GetActorLocation().Z - PlayerAltitude); // ���� �÷��̾��� ���� ������
	float MappedAltitude = UKismetMathLibrary::MapRangeClamped(CompPlayerAltitude, 0.f, 10.f, 0.7f, 0.f);
	*/
}
