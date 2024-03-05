// Fill out your copyright notice in the Description page of Project Settings.


#include "../Projectile/Bullet_Apache.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/GameFramework/ProjectileMovementComponent.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Components/SphereComponent.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/KismetMathLibrary.h>
#include "../Tank/TankBase.h"
#include "../Helicopter/Helicopter_Apache.h"
#include <../../../../../../../Plugins/FX/Niagara/Source/Niagara/Public/NiagaraFunctionLibrary.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Sound/SoundBase.h>
#include "../Component/StateComponent.h"
#include "../Buliding/Bunker.h"
#include "../Buliding/EnemyBuliding.h"

ABullet_Apache::ABullet_Apache()
{
	PrimaryActorTick.bCanEverTick = true;

	// 총알 콜리전
	HitCollision = CreateDefaultSubobject<USphereComponent>(TEXT("HitCollision"));
	SetRootComponent(HitCollision);

	// 총알 외형
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(RootComponent);
	MeshComp->SetRelativeRotation(FRotator(90, 0, 0));

	// 발사체 컴포넌트
	//MoveComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MoveComp"));

}

void ABullet_Apache::BeginPlay()
{
	Super::BeginPlay();

	/*
	FTimerHandle TimerHandle;
	float DelayInSeconds = 10.0f; // 파괴할 시간(초)을 설정

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this]()
		{
			// 타이머 콜백 함수 내에서 액터를 파괴
			Destroy();
		}, DelayInSeconds, false);
	*/

	float DelayInSeconds = 10.0f; // 파괴할 시간(초)을 설정

	SetLifeSpan(DelayInSeconds);

}

void ABullet_Apache::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 목표 위치로 부드럽게 이동
	FVector CurrentLocation = GetActorLocation();
	FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, 100000.f);
	SetActorLocation(NewLocation);

}

void ABullet_Apache::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), NSBullet, GetActorLocation(), FRotator(0), FVector(0.01f));


	if (OtherActor->GetComponentByClass<UStateComponent>()) {


		// ***** 데미지를 주는 방식으로 수정 필요 / 탱크가 갖고 있는 StateCompoenet의 함수를 호출할 것
		//UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), NSBullet, TargetLocation, FRotator(0), FVector(3));


		if (OtherActor->IsA<ATankBase>()) {

			// StateComponent를 이용해 체력을 감소시키는 방식으로 수정


			Cast<ATankBase>(OtherActor)->StateComponent->TakeDamage(20);

		}
		else if (OtherActor->IsA<ABunker>()) {

			Cast<ABunker>(OtherActor)->StateComponent->TakeDamage(20);


		}
		else if (OtherActor->IsA<AEnemyBuliding>()) {

			Cast<AEnemyBuliding>(OtherActor)->StateComponent->TakeDamage(20);


		}

	}

}

void ABullet_Apache::BulletMove(FVector TargetLoc)
{
	// 이동 수정 필요

	TargetLocation = TargetLoc;

}

void ABullet_Apache::SaveOwner()
{
	Apache = Cast<AHelicopter_Apache>(GetOwner());

}

void ABullet_Apache::setAttackDamage(float NewAttackDamage)
{

}
