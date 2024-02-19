// Fill out your copyright notice in the Description page of Project Settings.


#include "../AnimInstance/ApacheAnim.h"
#include "../Helicopter/Helicopter_Apache.h"

void UApacheAnim::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	Owner_Apache = Cast<AHelicopter_Apache>(GetOwningActor());

}

void UApacheAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!Owner_Apache) {
		return;
	}

	ABP_MainRoter_Z_Yaw = Owner_Apache->MainRotorSpeed;
	ABP_RearRotator_Y_Pitch = Owner_Apache->MainRotorSpeed;

}
