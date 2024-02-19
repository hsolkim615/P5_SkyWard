// Fill out your copyright notice in the Description page of Project Settings.


#include "../../Component/HeliComp/HeliTestComp.h"
#include <EnhancedInputComponent.h>
#include "../../Helicopter/Helicopter_Apache.h"
#include <ChaosVehicleMovementComponent.h>
#include <Kismet/KismetMathLibrary.h>
#include "HeliSoundComp.h"
#include <Kismet/KismetSystemLibrary.h>
#include "HeliMoveComp.h"

UHeliTestComp::UHeliTestComp()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UHeliTestComp::BeginPlay()
{
	Super::BeginPlay();

}

void UHeliTestComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
}

void UHeliTestComp::SetupPlayerInput(UInputComponent* PlayerInputComponent)
{

	Super::SetupPlayerInput(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	// 키보드 바인딩
	if (EnhancedInputComponent) {

		EnhancedInputComponent->BindAction(IA_Heli_FWD_BWD, ETriggerEvent::Triggered, this, &UHeliTestComp::FWD_BWD_Function);
		EnhancedInputComponent->BindAction(IA_Heli_FWD_BWD, ETriggerEvent::Canceled, this, &UHeliTestComp::FWD_BWD_Function);
		EnhancedInputComponent->BindAction(IA_Heli_FWD_BWD, ETriggerEvent::Completed, this, &UHeliTestComp::FWD_BWD_Function);

		EnhancedInputComponent->BindAction(IA_Heli_Up_Down, ETriggerEvent::Triggered, this, &UHeliTestComp::Up_Down_Function);
		EnhancedInputComponent->BindAction(IA_Heli_Up_Down, ETriggerEvent::Canceled, this, &UHeliTestComp::Up_Down_Function);
		EnhancedInputComponent->BindAction(IA_Heli_Up_Down, ETriggerEvent::Completed, this, &UHeliTestComp::Up_Down_Function);

		EnhancedInputComponent->BindAction(IA_Heli_Roll_Left_Right, ETriggerEvent::Triggered, this, &UHeliTestComp::Roll_Left_Right_Function);
		EnhancedInputComponent->BindAction(IA_Heli_Roll_Left_Right, ETriggerEvent::Canceled, this, &UHeliTestComp::Roll_Left_Right_Function);
		EnhancedInputComponent->BindAction(IA_Heli_Roll_Left_Right, ETriggerEvent::Completed, this, &UHeliTestComp::Roll_Left_Right_Function);

		EnhancedInputComponent->BindAction(IA_Heli_Steering, ETriggerEvent::Triggered, this, &UHeliTestComp::Steering_Function);
		EnhancedInputComponent->BindAction(IA_Heli_Steering, ETriggerEvent::Canceled, this, &UHeliTestComp::Steering_Function);
		EnhancedInputComponent->BindAction(IA_Heli_Steering, ETriggerEvent::Completed, this, &UHeliTestComp::Steering_Function);

		EnhancedInputComponent->BindAction(IA_Free_Look_Key, ETriggerEvent::Triggered, this, &UHeliTestComp::Free_Look_Key_Function);
		EnhancedInputComponent->BindAction(IA_Free_Look_Key, ETriggerEvent::Canceled, this, &UHeliTestComp::Free_Look_Key_Function);
		EnhancedInputComponent->BindAction(IA_Free_Look_Key, ETriggerEvent::Completed, this, &UHeliTestComp::Free_Look_Key_Function);

		EnhancedInputComponent->BindAction(IA_Free_Look, ETriggerEvent::Triggered, this, &UHeliTestComp::Free_Look_Function);
		EnhancedInputComponent->BindAction(IA_Free_Look, ETriggerEvent::Canceled, this, &UHeliTestComp::Free_Look_Function);
		EnhancedInputComponent->BindAction(IA_Free_Look, ETriggerEvent::Completed, this, &UHeliTestComp::Free_Look_Function);

		// 엔진 시동 
		EnhancedInputComponent->BindAction(IA_On_Off, ETriggerEvent::Started, this, &UHeliTestComp::On_Off_Function);

	}

}

void UHeliTestComp::FWD_BWD_Function(const FInputActionValue& value)
{

	float PitchValue = value.Get<float>();

	Apache->AddControllerPitchInput(PitchValue);

	Apache->GetVehicleMovementComponent()->SetPitchInput(PitchValue);

}

void UHeliTestComp::Up_Down_Function(const FInputActionValue& value)
{

	HeliComp_Move->ActionValueUpDown = value.Get<float>();
	
	//UE_LOG(LogTemp, Warning, TEXT("float : %f"), ActionValueUpDown);

	if (HeliComp_Move->ActionValueUpDown == 0) {

		HeliComp_Move->ApacheAltitude = Apache->GetActorLocation().Z;

	}

}

void UHeliTestComp::Roll_Left_Right_Function(const FInputActionValue& value)
{

	float RollValue = value.Get<float>();

	Apache->AddControllerRollInput(RollValue);

	Apache->GetVehicleMovementComponent()->SetRollInput(RollValue);


}

void UHeliTestComp::Steering_Function(const FInputActionValue& value)
{

	float YawValue = value.Get<float>();

	Apache->AddControllerYawInput(YawValue);

	Apache->GetVehicleMovementComponent()->SetYawInput(YawValue);

}

void UHeliTestComp::Free_Look_Key_Function(const FInputActionValue& value)
{

	Apache->AddControllerPitchInput(Look_Function_VecterValue_Y / 2);

}

void UHeliTestComp::Free_Look_Function(const FInputActionValue& value)
{

	FVector2D VecterValue = value.Get<FVector2D>();

	Apache->AddControllerYawInput(VecterValue.X / 2);

	Look_Function_VecterValue_Y = VecterValue.Y;

}

void UHeliTestComp::On_Off_Function(const FInputActionValue& value)
{
	
	HeliComp_Move->On_Off_Function(value);

}
