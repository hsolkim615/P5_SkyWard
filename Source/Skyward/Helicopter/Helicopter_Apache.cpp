// Fill out your copyright notice in the Description page of Project Settings.


#include "../Helicopter/Helicopter_Apache.h"
#include <HeadMountedDisplayFunctionLibrary.h>
#include <EnhancedInputSubsystems.h>
#include "../Component/HeliComp/HeliMoveComp.h"
#include "../Component/HeliComp/HeliSoundComp.h"

AHelicopter_Apache::AHelicopter_Apache()
{
	PrimaryActorTick.bCanEverTick = true;

	// ÀÌµ¿ ÄÄÆ÷³ÍÆ®
	MoveComp = CreateDefaultSubobject<UHeliMoveComp>(TEXT("MoveComp"));
	
	SoundComp = CreateDefaultSubobject<UHeliSoundComp>(TEXT("SoundComp"));

}

void AHelicopter_Apache::BeginPlay()
{
	Super::BeginPlay();

	// EnhancedInput ¸ÊÇÎ ¼³Á¤ - IMC_Heli ===================================================
	UHeadMountedDisplayFunctionLibrary::SetTrackingOrigin(EHMDTrackingOrigin::Stage);

	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController()) {
		UEnhancedInputLocalPlayerSubsystem* subsys = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

		if (subsys != nullptr && IMC_Heli != nullptr) {
			subsys->AddMappingContext(IMC_Heli, 0);

		}
	}
	// EnhancedInput ¸ÊÇÎ ¼³Á¤ - IMC_Heli ===================================================

}

void AHelicopter_Apache::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

void AHelicopter_Apache::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	/*
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (EnhancedInputComponent) {
		EnhancedInputComponent->BindAction(IA_Heli_FWD_BWD, ETriggerEvent::Triggered, this, &AHelicopter_Apache::FWD_BWD_Function);
		EnhancedInputComponent->BindAction(IA_Heli_Up_Down, ETriggerEvent::Triggered, this, &AHelicopter_Apache::Up_Down_Function);
		EnhancedInputComponent->BindAction(IA_Heli_Roll_Left_Right, ETriggerEvent::Triggered, this, &AHelicopter_Apache::Roll_Left_Right_Function);
		EnhancedInputComponent->BindAction(IA_Heli_Steering, ETriggerEvent::Triggered, this, &AHelicopter_Apache::Steering_Function);
	}
	*/

	OnSetupInputDelegate.Broadcast(PlayerInputComponent);

}

