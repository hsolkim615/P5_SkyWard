// Fill out your copyright notice in the Description page of Project Settings.


#include "../Projectile/Missile_Apache.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Components/SphereComponent.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Components/SkeletalMeshComponent.h>
#include "../Helicopter/Helicopter_Apache.h"
#include "../Tank/TankBase.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/KismetMathLibrary.h>
#include <../../../../../../../Plugins/FX/Niagara/Source/Niagara/Public/NiagaraComponent.h>

AMissile_Apache::AMissile_Apache()
{
	PrimaryActorTick.bCanEverTick = true;

	HitCollision = CreateDefaultSubobject<USphereComponent>(TEXT("HitCollision"));
	SetRootComponent(HitCollision);

	// 총알 외형
	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(RootComponent);

	NSComp = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NSComp"));
	NSComp->SetupAttachment(RootComponent);
	NSComp->SetRelativeLocation(FVector(-150, 0, 0));

}

void AMissile_Apache::BeginPlay()
{
	Super::BeginPlay();
	NSComp->SetActive(false);

}

void AMissile_Apache::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (EngineOn == false) {
		return;
	}

	/*
	// 목표 위치로 부드럽게 이동
	FVector CurrentLocation = GetActorLocation();
	FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, 2000.f);
	SetActorLocation(NewLocation);
	*/


	// 현재 속도가 최대 속도보다 작을 때 가속
	if (CurrentSpeed < MaxSpeed) {
		CurrentSpeed += MissileAcceleration * DeltaTime;
	}

	// 목표 위치로 부드럽게 이동
	FVector CurrentLocation = GetActorLocation();
	FVector Direction = (TargetLocation - CurrentLocation).GetSafeNormal();
	FVector NewLocation = CurrentLocation + Direction * CurrentSpeed * DeltaTime;
	SetActorLocation(NewLocation);

}

void AMissile_Apache::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (OtherActor->IsA<ATankBase>()) {

		FRotator MissileDirection = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TargetLocation);

		SetActorRelativeRotation(MissileDirection);

		// ***** 데미지를 주는 방식으로 수정 필요 / 탱크가 갖고 있는 StateCompoenet의 함수를 호출할 것
		OtherActor->Destroy();

		Destroy();

	}

}

void AMissile_Apache::SaveOwner()
{
	OwnerHeli = Cast<AHelicopter_Apache>(GetOwner());

}

void AMissile_Apache::MissileMove(FVector TargetLoc)
{
	TargetLocation = TargetLoc;

	EngineOn = true;

	// 이펙트 연출

}

