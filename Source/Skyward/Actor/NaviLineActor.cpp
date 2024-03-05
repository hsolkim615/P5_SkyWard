// Fill out your copyright notice in the Description page of Project Settings.


#include "../Actor/NaviLineActor.h"
#include "../Helicopter/Helicopter_Apache.h"
#include <../../../../../../../Source/Runtime/Engine/Public/EngineUtils.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Camera/CameraComponent.h>

// Sets default values
ANaviLineActor::ANaviLineActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ANaviLineActor::BeginPlay()
{
	Super::BeginPlay();

	for (TActorIterator<AHelicopter_Apache> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		// AHelicopter_Apache 클래스의 액터인지 확인
		Apache = *ActorItr;

		break;
	}

}

// Called every frame
void ANaviLineActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

