// Fill out your copyright notice in the Description page of Project Settings.


#include "../../Component/HeliComp/HeliCompBase.h"
#include "../../Helicopter/Helicopter_Apache.h"
#include "HeliMoveComp.h"
#include "HeliSoundComp.h"
#include "HeliAttackComp.h"

// Sets default values for this component's properties
UHeliCompBase::UHeliCompBase()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	bWantsInitializeComponent = true;
}


// Called when the game starts
void UHeliCompBase::BeginPlay()
{
	Super::BeginPlay();

	// ...
	

}

void UHeliCompBase::InitializeComponent()
{
	Super::InitializeComponent();

	Apache = Cast<AHelicopter_Apache>(GetOwner());

	HeliComp_Move = Cast<UHeliMoveComp>(Apache->MoveComp);

	HeliComp_Attack = Cast<UHeliAttackComp>(Apache->AttackComp);
	
	HeliComp_Sound = Cast<UHeliSoundComp>(Apache->SoundComp);



	Apache->OnSetupInputDelegate.AddUObject(this, &UHeliCompBase::SetupPlayerInput);



}


// Called every frame
void UHeliCompBase::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHeliCompBase::SetupPlayerInput(UInputComponent* PlayerInputComponent)
{
}

