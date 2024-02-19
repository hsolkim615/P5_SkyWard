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

		// ��� �Ҹ� ȣ��
		if (HeliComp_Sound) {
			HeliComp_Sound->PlayHeliSound_Engine();
		}

		// ��� ������ 
		MainRotorSpeedRate = FMath::FInterpTo(MainRotorSpeedRate, 25.f, DeltaTime, 0.2f); // �ְ�ӷ� 25

		// �ִϸ��̼ǿ��� ��� - �����緯 ȸ��
		Apache->MainRotorSpeed += MainRotorSpeedRate;

		// MainRotorSpeedRate�� ������ Ű�� �ڵ����� �ö�
		if (MainRotorSpeedRate >= 15.f) {

			if (ActionValueUpDown == 0) {

				// �� ���� ���
				HoldHeliAltitude();

			}
			else
			{
				Apache->GetVehicleMovement()->SetThrottleInput(ActionValueUpDown);
			}

		}

	}
	else { // ��� ���� ����
		// ��� �Ҹ� ȣ�� - �õ����� �Ҹ�
		if (HeliComp_Sound) {
			HeliComp_Sound->PlayHeliSound_Engine();
		}

		// ��� ������
		MainRotorSpeedRate = FMath::FInterpTo(MainRotorSpeedRate, 0, DeltaTime, 1.f); // �ְ�ӷ� 25

		// �ִϸ��̼ǿ��� ��� - �����緯 ȸ��
		Apache->MainRotorSpeed += MainRotorSpeedRate;
	}





	// ��� ���� �α� -------------------------------------------------------
	CurrentPitch = Apache->GetActorRotation().Pitch;
	CurrentRoll = Apache->GetActorRotation().Roll;


	UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("VehicleMovementComponent Pitch: %f"), CurrentPitch), true, false, FLinearColor::Green, 5.0f, FName(TEXT("VehiclePitch")));
	UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("VehicleMovementComponent Roll: %f"), CurrentRoll), true, false, FLinearColor::Green, 5.0f, FName(TEXT("VehicleRoll")));

}

void UHeliMoveComp::SetupPlayerInput(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInput(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	// VR ��Ʈ�ѷ� ���ε�
	if (EnhancedInputComponent) {
		
		// ��� ����(����)
		EnhancedInputComponent->BindAction(IA_Apache_Cyclic, ETriggerEvent::Triggered, this, &UHeliMoveComp::Cyclie_RightThumbStick);
		EnhancedInputComponent->BindAction(IA_Apache_Cyclic, ETriggerEvent::Canceled, this, &UHeliMoveComp::Cyclie_RightThumbStick);
		EnhancedInputComponent->BindAction(IA_Apache_Cyclic, ETriggerEvent::Completed, this, &UHeliMoveComp::Cyclie_RightThumbStick);

		// ��� ��
		EnhancedInputComponent->BindAction(IA_Apache_Collective, ETriggerEvent::Triggered, this, &UHeliMoveComp::Collective_LeftGrip);
		EnhancedInputComponent->BindAction(IA_Apache_Collective, ETriggerEvent::Canceled, this, &UHeliMoveComp::Collective_LeftGrip);
		EnhancedInputComponent->BindAction(IA_Apache_Collective, ETriggerEvent::Completed, this, &UHeliMoveComp::Collective_LeftGrip);

		// ��� ȸ��
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

		// ����� ��������� �����ϴ� ����Ʈ���̽�
		GetWorld()->LineTraceSingleByChannel(hitResult, startLoc, endLoc, ECC_Visibility, CollisionParams);

		DrawDebugLine(GetWorld(), startLoc, endLoc, FColor::Red, false, 0, 0, 5);

		if (hitResult.bBlockingHit == true) {

			bIsEngineOnOff = false;

			Apache->GetVehicleMovementComponent()->SetHandbrakeInput(true);

		}

	}

}

// VR ��Ʈ�ѷ� ==========================================================================

void UHeliMoveComp::Cyclie_RightThumbStick(const FInputActionValue& value)
{
	FVector2D VecterValue = value.Get<FVector2D>();

	//UKismetSystemLibrary::PrintString(const UObject * WorldContextObject, const FString & InString, bool bPrintToScreen, bool bPrintToLog, FLinearColor TextColor, float Duration, const FName Key)

	UKismetSystemLibrary::PrintString(this, VecterValue.ToString(), true, false, FLinearColor::Green, 5.0f, FName(TEXT("VecterValue")));

	/*
	// �̴�� �ϸ� �潺ƽ�� �� �Է����� �ʾƵ� ��Ⱑ ��� ȸ����

	// ����, ����
	if (VecterValue.Y != 0) {

		Apache->AddControllerPitchInput(VecterValue.Y);

		Apache->GetVehicleMovementComponent()->SetPitchInput(VecterValue.Y);

	}

	// ������, ����
	if (VecterValue.X != 0) {
		Apache->AddControllerRollInput(VecterValue.X);

		Apache->GetVehicleMovementComponent()->SetRollInput(VecterValue.X);

	}
	*/


	// �� ��ƽ�� ��￩�� ������ ����Ͽ� ����� ��ü�� ��￩���� ��.(������ ���� 0 ~ 1 ������ ���� float�� ��ȯ��)
	// �ִ� ���� 30��
	// ������ ���Ǽ��� ���� ��ƽ�� �ΰ����� ������ �ʿ䰡 ���� -> �Է� ���� 0.5 �̻��� ������ 0 ~ 30�� ���̷� ��￩��
	// Ȥ�� �� ���� �Է��� ������ �ٸ� �Էº��� ũ��, ū ������ ��￩��


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


	/*
	if (VecterValue != FVector2D::ZeroVector) {
		// �Է¿� ���� ���� ����

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
		// �Է��� ������ ���� ���� ����
		StopUpdatingHelicopterAngle();
	}
	*/


	/*
	// �Է°��� 0�� �ƴ� ��쿡�� ���� ����
	if (VecterValue != FVector2D::ZeroVector) {
		// �Է¿� ���� ���� ����
		UpdateHelicopterAngle(VecterValue);
	}
	else {
		// �Է��� ������ ���� ���� ����
		StopUpdatingHelicopterAngle();
	}
	*/


}

void UHeliMoveComp::UpdateHelicopterAngle(const FVector2D& InputValue)
{
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
	// value���� ���� �ϰ�, ����, ��·� ����� ���� ����
	// �޼� �׷��� ��ȯ ���� ���� �ܰ踦 0~4�� ������, �� �ܰ迡 ���� ���� �޶�����. - �ִ� 7000m



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
		// -> 0�� ���� �� ����, ����� ���� ���� ���� �ϰ�, ���� ���� ���, 1�� ���� ����ϵ��� �۵� �� 
	}

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
	
	// Out Range A �κ��� �ٲپ� ���� ���� �ٲ� �� ���� -> �ʹ� ũ�� ��鸲�� ���ϰ�, �ʹ� ������ ��Ⱑ �߶���
	float Altitude = UKismetMathLibrary::MapRangeClamped(Apache->GetActorLocation().Z - ApacheAltitude, 0.f, 10.f, 0.7f, 0.f);

	Apache->GetVehicleMovement()->SetThrottleInput(Altitude);


	/*
	// �� ���� ���
	double CompPlayerAltitude = (Apache->GetActorLocation().Z - PlayerAltitude); // ���� �÷��̾��� ���� ������
	float MappedAltitude = UKismetMathLibrary::MapRangeClamped(CompPlayerAltitude, 0.f, 10.f, 0.7f, 0.f);
	*/
}
