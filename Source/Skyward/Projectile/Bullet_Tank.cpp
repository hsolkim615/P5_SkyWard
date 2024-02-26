// Fill out your copyright notice in the Description page of Project Settings.


#include "../Projectile/Bullet_Tank.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Components/SphereComponent.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Components/StaticMeshComponent.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/GameFramework/ProjectileMovementComponent.h>
#include "../Helicopter/HelicopterBase.h"

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


	Player = Cast<AHelicopterBase>(GetOwner());

	if (Player)
	{
		float DistanceToTarget = FVector::Distance(GetActorLocation(), Player->GetActorLocation());
	

		// 거리에 따라 초기 속도를 계산
		float InitialSpeed = FMath::Lerp(MinSpeed, MaxSpeed, FMath::Clamp(DistanceToTarget / MaxDistance, 0.0f, 1.0f));

		// Projectile Movement Component에 초기 속도 설정
		MovementComp->InitialSpeed = InitialSpeed;
	}
}

