// Fill out your copyright notice in the Description page of Project Settings.


#include "../Projectile/Bullet_Apache.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/GameFramework/ProjectileMovementComponent.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Components/SphereComponent.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/KismetMathLibrary.h>

ABullet_Apache::ABullet_Apache()
{
	PrimaryActorTick.bCanEverTick = true;

	// 총알 콜리전
	HitCollision = CreateDefaultSubobject<USphereComponent>(TEXT("HitCollision"));
	SetRootComponent(HitCollision);
	HitCollision->SetRelativeScale3D(FVector(0.05f));

	// 총알 외형
	MeshComp->SetupAttachment(RootComponent);
	MeshComp->SetRelativeRotation(FRotator(90, 0, 0));
	MeshComp->SetRelativeScale3D(FVector(0.5f, 0.5, 1.f));

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
	FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, 10000.f);
	SetActorLocation(NewLocation);



}

void ABullet_Apache::BulletMove(FVector TargetLoc)
{
	// 이동 수정 필요

	/*
	FVector TargetLocation = GetActorLocation();
	FRotator TargetRotation = HitCollision->GetComponentRotation();
	float MoveTime = UKismetMathLibrary::Vector_Distance(TargetLocation, TargetLoc) / 500.f; // 이동에 걸리는 시간 계산

	// MoveComponentTo 함수를 호출하여 HitCollision을 TargetLocation으로 이동시킵니다.
	UKismetSystemLibrary::MoveComponentTo(HitCollision, TargetLocation, HitCollision->GetComponentRotation(), false, false, MoveTime, false, EMoveComponentAction::Type::Move, FLatentActionInfo());
	*/

	TargetLocation = TargetLoc;


}
