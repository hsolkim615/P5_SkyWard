// Fill out your copyright notice in the Description page of Project Settings.


#include "../../Component/HeliComp/HeliSoundComp.h"
#include <Components/AudioComponent.h>
#include "HeliMoveComp.h"
#include "../../Helicopter/Helicopter_Apache.h"

UHeliSoundComp::UHeliSoundComp()
{
	HeliSoundPropComp = CreateDefaultSubobject<UAudioComponent>(TEXT("HeliSoundComp"));
}

void UHeliSoundComp::BeginPlay()
{
	Super::BeginPlay();

	if (HeliPropSound) {
		HeliSoundPropComp->SetSound(HeliPropSound);

	}


}

void UHeliSoundComp::PlayHeliSound_Engine()
{

	HeliSoundPropComp->SetFloatParameter(FName("RotorSound"),HeliComp_Move->MainRotorSpeedRate);

}
