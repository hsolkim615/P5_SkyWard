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
		
		// 헬기 소리 호출
		if (HeliComp_Sound) {
			HeliComp_Sound->PlayHeliSound_Engine();
		}

		// 헬기 움직임
		MainRotorSpeedRate = FMath::FInterpTo(MainRotorSpeedRate, 25.f, DeltaTime, 0.2f); // 최고속력 25

		// 애니메이션에서 사용 - 프로펠러 회전
		Apache->MainRotorSpeed += MainRotorSpeedRate;

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
	else {
		// 헬기 소리 호출
		if (HeliComp_Sound) {
			HeliComp_Sound->PlayHeliSound_Engine();
		}

		// 헬기 움직임
		MainRotorSpeedRate = FMath::FInterpTo(MainRotorSpeedRate, 0, DeltaTime, 1.f); // 최고속력 25

		// 애니메이션에서 사용 - 프로펠러 회전
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

	// 왼손 그랩의 반환 값에 따라 단계를 0~4로 나누고, 각 단계에 따라 고도가 달라진다. - 최대 7000m


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

		// 지면과 가까운지를 감지하는 라인트레이스
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
	// Out Range A 부분을 바꾸어 유지 고도를 바꿀 수 있음 -> 너무 크면 흔들림이 심하고, 너무 작으면 헬기가 추락함
	float Altitude = UKismetMathLibrary::MapRangeClamped(Apache->GetActorLocation().Z - ApacheAltitude, 0.f, 10.f, 0.7f, 0.f);

	Apache->GetVehicleMovement()->SetThrottleInput(Altitude);


	/*
	// 고도 유지 기능
	double CompPlayerAltitude = (Apache->GetActorLocation().Z - PlayerAltitude); // 현재 플레이어의 고도를 가져옴
	float MappedAltitude = UKismetMathLibrary::MapRangeClamped(CompPlayerAltitude, 0.f, 10.f, 0.7f, 0.f);
	*/
}
