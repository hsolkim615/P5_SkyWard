// Fill out your copyright notice in the Description page of Project Settings.


#include "../Projectile/Bullet_Tank.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Components/CapsuleComponent.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Components/StaticMeshComponent.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/GameFramework/ProjectileMovementComponent.h>
#include "../Helicopter/HelicopterBase.h"
#include <../../../../../../../Plugins/FX/Niagara/Source/Niagara/Public/NiagaraFunctionLibrary.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Engine/TimerHandle.h>
#include <../../../../../../../Source/Runtime/Engine/Public/TimerManager.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h>
#include "../Helicopter/Helicopter_Apache.h"
#include "../Buliding/Bunker.h"
#include "../Component/StateComponent.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Components/SphereComponent.h>

// Sets default values
ABullet_Tank::ABullet_Tank()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComp"));
	SetRootComponent(CollisionComp);
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


	FTimerManager& TimerManager = GetWorld()->GetTimerManager();
	FTimerHandle TimerHandle;

	TimerManager.SetTimer(TimerHandle, this, &ABullet_Tank::BulletDestroy, DelayInSeconds, true);
}

// Called every frame
void ABullet_Tank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	//Player = Cast<AHelicopterBase>(GetOwner());

	//if (Player)
	//{
	//	float DistanceToTarget = FVector::Distance(GetActorLocation(), Player->GetActorLocation());


	//	// 거리에 따라 초기 속도를 계산
	//	float InitialSpeed = FMath::Lerp(MinSpeed, MaxSpeed, FMath::Clamp(DistanceToTarget / MaxDistance, 0.0f, 1.0f));

	//	// Projectile Movement Component에 초기 속도 설정
	//	MovementComp->InitialSpeed = InitialSpeed;
	//}
}

void ABullet_Tank::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (OtherActor->GetComponentByClass<UStateComponent>()) {

		if (OtherActor->IsA<AHelicopter_Apache>()) {

			/*if (Flame_Damage)
			{
				UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Flame_Damage, GetActorLocation(), GetActorRotation());

			}*/

			// 데미지
			//OtherActor->Destroy();

			Cast<AHelicopter_Apache>(OtherActor)->StateComponent->TakeDamage(AttackDamage);

			Destroy();
		}
		else if (OtherActor->IsA<ABunker>()) {

			Cast<ABunker>(OtherActor)->StateComponent->TakeDamage(AttackDamage);

			Destroy();
		}

	}



}

void ABullet_Tank::BulletDestroy()
{
	Destroy();
}


