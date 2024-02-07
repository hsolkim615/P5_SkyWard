// Fill out your copyright notice in the Description page of Project Settings.


#include "../../Component/HeliComp/HeliMoveComp.h"
#include <EnhancedInputComponent.h>
#include "../../Helicopter/Helicopter_Apache.h"
#include <ChaosVehicleMovementComponent.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/KismetMathLibrary.h>
#include "HeliSoundComp.h"

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

	if (bIsEngineOnOff) {
		
		// ��� �Ҹ� ȣ��
		if (HeliComp_Sound) {
			HeliComp_Sound->PlayHeliSound_Engine();
		}

		// ��� ������
		MainRotorSpeedRate = FMath::FInterpTo(MainRotorSpeedRate, 25.f, DeltaTime, 0.2f); // �ְ�ӷ� 25

		// �ִϸ��̼ǿ��� ��� - �����緯 ȸ��
		Apache->MainRotorSpeed += MainRotorSpeedRate;

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
	else {
		// ��� �Ҹ� ȣ��
		if (HeliComp_Sound) {
			HeliComp_Sound->PlayHeliSound_Engine();
		}

		// ��� ������
		MainRotorSpeedRate = FMath::FInterpTo(MainRotorSpeedRate, 0, DeltaTime, 1.f); // �ְ�ӷ� 25

		// �ִϸ��̼ǿ��� ��� - �����緯 ȸ��
		Apache->MainRotorSpeed += MainRotorSpeedRate;
	}

	
	

}

void UHeliMoveComp::SetupPlayerInput(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInput(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (EnhancedInputComponent) {

		EnhancedInputComponent->BindAction(IA_Heli_FWD_BWD, ETriggerEvent::Triggered, this, &UHeliMoveComp::FWD_BWD_Function);
		EnhancedInputComponent->BindAction(IA_Heli_FWD_BWD, ETriggerEvent::Canceled, this, &UHeliMoveComp::FWD_BWD_Function);
		EnhancedInputComponent->BindAction(IA_Heli_FWD_BWD, ETriggerEvent::Completed, this, &UHeliMoveComp::FWD_BWD_Function);

		EnhancedInputComponent->BindAction(IA_Heli_Up_Down, ETriggerEvent::Triggered, this, &UHeliMoveComp::Up_Down_Function);
		EnhancedInputComponent->BindAction(IA_Heli_Up_Down, ETriggerEvent::Canceled, this, &UHeliMoveComp::Up_Down_Function);
		EnhancedInputComponent->BindAction(IA_Heli_Up_Down, ETriggerEvent::Completed, this, &UHeliMoveComp::Up_Down_Function);

		EnhancedInputComponent->BindAction(IA_Heli_Roll_Left_Right, ETriggerEvent::Triggered, this, &UHeliMoveComp::Roll_Left_Right_Function);
		EnhancedInputComponent->BindAction(IA_Heli_Roll_Left_Right, ETriggerEvent::Canceled, this, &UHeliMoveComp::Roll_Left_Right_Function);
		EnhancedInputComponent->BindAction(IA_Heli_Roll_Left_Right, ETriggerEvent::Completed, this, &UHeliMoveComp::Roll_Left_Right_Function);

		EnhancedInputComponent->BindAction(IA_Heli_Steering, ETriggerEvent::Triggered, this, &UHeliMoveComp::Steering_Function);
		EnhancedInputComponent->BindAction(IA_Heli_Steering, ETriggerEvent::Canceled, this, &UHeliMoveComp::Steering_Function);
		EnhancedInputComponent->BindAction(IA_Heli_Steering, ETriggerEvent::Completed, this, &UHeliMoveComp::Steering_Function);

		EnhancedInputComponent->BindAction(IA_Free_Look_Key, ETriggerEvent::Triggered, this, &UHeliMoveComp::Free_Look_Key_Function);
		EnhancedInputComponent->BindAction(IA_Free_Look_Key, ETriggerEvent::Canceled, this, &UHeliMoveComp::Free_Look_Key_Function);
		EnhancedInputComponent->BindAction(IA_Free_Look_Key, ETriggerEvent::Completed, this, &UHeliMoveComp::Free_Look_Key_Function);

		EnhancedInputComponent->BindAction(IA_Free_Look, ETriggerEvent::Triggered, this, &UHeliMoveComp::Free_Look_Function);
		EnhancedInputComponent->BindAction(IA_Free_Look, ETriggerEvent::Canceled, this, &UHeliMoveComp::Free_Look_Function);
		EnhancedInputComponent->BindAction(IA_Free_Look, ETriggerEvent::Completed, this, &UHeliMoveComp::Free_Look_Function);



		EnhancedInputComponent->BindAction(IA_On_Off, ETriggerEvent::Started, this, &UHeliMoveComp::On_Off_Function);


	}

}

void UHeliMoveComp::FWD_BWD_Function(const FInputActionValue& value)
{

	//bool PitchValue = value.Get<bool>();

	float PitchValue = value.Get<float>();


	Apache->AddControllerPitchInput(PitchValue);

	Apache->GetVehicleMovementComponent()->SetPitchInput(PitchValue);

}

void UHeliMoveComp::Up_Down_Function(const FInputActionValue& value)
{

	ActionValueUpDown = value.Get<float>();

	//UE_LOG(LogTemp, Warning, TEXT("float : %f"), ActionValueUpDown);

	if (ActionValueUpDown == 0) {

		ApacheAltitude = Apache->GetActorLocation().Z;

	}

	// �޼� �׷��� ��ȯ ���� ���� �ܰ踦 0~4�� ������, �� �ܰ迡 ���� ���� �޶�����. - �ִ� 7000m


	if (ActionValueUpDown == 0) {

	}


}

void UHeliMoveComp::Roll_Left_Right_Function(const FInputActionValue& value)
{

	float RollValue = value.Get<float>();

	Apache->AddControllerRollInput(RollValue);

	Apache->GetVehicleMovementComponent()->SetRollInput(RollValue);


}

void UHeliMoveComp::Steering_Function(const FInputActionValue& value)
{

	float YawValue = value.Get<float>();

	Apache->AddControllerYawInput(YawValue);

	Apache->GetVehicleMovementComponent()->SetYawInput(YawValue);


}

void UHeliMoveComp::Free_Look_Key_Function(const FInputActionValue& value)
{

	//UE_LOG(LogTemp, Warning, TEXT("Success1"));

	Apache->AddControllerPitchInput(Look_Function_VecterValue_Y / 2);

}

void UHeliMoveComp::Free_Look_Function(const FInputActionValue& value)
{

	FVector2D VecterValue = value.Get<FVector2D>();

	Apache->AddControllerYawInput(VecterValue.X / 2);

	Look_Function_VecterValue_Y = VecterValue.Y;

}

void UHeliMoveComp::On_Off_Function(const FInputActionValue& value)
{
	if (bIsEngineOnOff == false) {
		
		bIsEngineOnOff = true;
		
		Apache->GetVehicleMovementComponent()->SetHandbrakeInput(false);

	}
	else if(bIsEngineOnOff == true) {
		
		FHitResult hitResult;
		FVector startLoc = Apache->GetActorLocation() + FVector(0,0,50);
		FVector endLoc = Apache->GetActorLocation() + FVector(0, 0, -10);

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

void UHeliMoveComp::HoldHeliAltitude()
{
	// Out Range A �κ��� �ٲپ� ���� ���� �ٲ� �� ���� -> �ʹ� ũ�� ��鸲�� ���ϰ�, �ʹ� ������ ��Ⱑ �߶���
	float Altitude = UKismetMathLibrary::MapRangeClamped(Apache->GetActorLocation().Z - ApacheAltitude, 0.f, 10.f, 0.7f, 0.f);

	Apache->GetVehicleMovement()->SetThrottleInput(Altitude);


	/*
	// �� ���� ���
	double CompPlayerAltitude = (Apache->GetActorLocation().Z - PlayerAltitude); // ���� �÷��̾��� ���� ������
	float MappedAltitude = UKismetMathLibrary::MapRangeClamped(CompPlayerAltitude, 0.f, 10.f, 0.7f, 0.f);
	*/
}
