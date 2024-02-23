// Fill out your copyright notice in the Description page of Project Settings.


#include "../Actor/Path.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Components/SplineComponent.h>

// Sets default values
APath::APath()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SplineComp = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComp"));
	
}

// Called when the game starts or when spawned
void APath::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APath::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}

