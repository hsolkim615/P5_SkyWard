// Fill out your copyright notice in the Description page of Project Settings.


#include "../Tank/TankBase.h"

#include "Components/BoxComponent.h"

ATankBase::ATankBase()
{
	PrimaryActorTick.bCanEverTick = true;
 
	// boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	// SetRootComponent(boxComp);
	//
	// meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	// meshComp->SetupAttachment(boxComp); 
}
