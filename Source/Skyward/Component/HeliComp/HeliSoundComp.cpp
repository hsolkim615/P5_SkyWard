// Fill out your copyright notice in the Description page of Project Settings.


#include "../../Component/HeliComp/HeliSoundComp.h"
#include <Components/AudioComponent.h>
#include "HeliMoveComp.h"
#include "../../Helicopter/Helicopter_Apache.h"

UHeliSoundComp::UHeliSoundComp()
{
	HeliSoundComp = CreateDefaultSubobject<UAudioComponent>(TEXT("HeliSoundComp"));
}

void UHeliSoundComp::BeginPlay()
{
	Super::BeginPlay();

	if (HeliSound) {
		HeliSoundComp->SetSound(HeliSound);

	}


}

void UHeliSoundComp::PlayHeliSound_Engine()
{
	UE_LOG(LogTemp, Warning, TEXT("PlaySound"));

	HeliSoundComp->SetFloatParameter(FName("RotorSound"),HeliComp_Move->MainRotorSpeedRate);

}
