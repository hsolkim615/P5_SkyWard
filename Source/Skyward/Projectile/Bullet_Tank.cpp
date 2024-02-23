// Fill out your copyright notice in the Description page of Project Settings.


#include "../Projectile/Bullet_Tank.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Components/SphereComponent.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Components/StaticMeshComponent.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/GameFramework/ProjectileMovementComponent.h>

// Sets default values
ABullet_Tank::ABullet_Tank()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComp"));
	RootComponent = CollisionComp;
	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("meshComp"));
	meshComp->SetupAttachment(CollisionComp);
	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComp"));
	//MovementComp->MaxSpeed = 0;
	//MovementComp->InitialSpeed = 0;
	 

}

// Called when the game starts or when spawned
void ABullet_Tank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABullet_Tank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

