// Fill out your copyright notice in the Description page of Project Settings.


#include "../Projectile/Missile_Apache.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Components/SphereComponent.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Components/SkeletalMeshComponent.h>
#include "../Helicopter/Helicopter_Apache.h"
#include "../Tank/TankBase.h"
#include <../../../../../../../Plugins/FX/Niagara/Source/Niagara/Public/NiagaraComponent.h>
#include <../../../../../../../Plugins/FX/Niagara/Source/Niagara/Public/NiagaraFunctionLibrary.h>
#include <../../../../../../../Plugins/FX/Niagara/Source/Niagara/Classes/NiagaraSystem.h>
#include "../Buliding/Bunker.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Sound/SoundBase.h>
#include "HydraMissile_Apache.h"

AMissile_Apache::AMissile_Apache()
{
	PrimaryActorTick.bCanEverTick = true;

	HitCollision = CreateDefaultSubobject<USphereComponent>(TEXT("HitCollision"));
	SetRootComponent(HitCollision);
	HitCollision->SetSphereRadius(15.f);

	// 총알 외형
	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(RootComponent);
	MeshComp->SetRelativeLocation(FVector(-63, 0, 0));

	NSComp = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NSComp"));
	NSComp->SetupAttachment(RootComponent);
	NSComp->SetRelativeLocation(FVector(-150, 0, 0));

}

void AMissile_Apache::BeginPlay()
{
	Super::BeginPlay();


	// HitCollision과 overlap되었을 때 호출
	HitCollision->OnComponentBeginOverlap.AddDynamic(this, &AMissile_Apache::OnOverlapBegin);

	NSComp->SetActive(false);

}

void AMissile_Apache::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (EngineOn == false) {
		return;
	}


	// 현재 속도가 최대 속도보다 작을 때 가속
	if (CurrentSpeed < MaxSpeed) {
		CurrentSpeed += MissileAcceleration * DeltaTime;
	}

	// 목표 위치로 부드럽게 이동
	FVector CurrentLocation = GetActorLocation();
	FVector Direction = (TargetLocation - CurrentLocation).GetSafeNormal();
	FVector NewLocation = CurrentLocation + Direction * CurrentSpeed * DeltaTime;
	SetActorLocation(NewLocation);
	
	if (FVector::Distance(GetActorLocation(), TargetLocation) <= 200) {
		BoomMissile();
	}

	

}

void AMissile_Apache::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (!OtherActor->IsA<AHelicopter_Apache>() && !OtherActor->IsA<AMissile_Apache>() && !OtherActor->IsA<AHydraMissile_Apache>()) {
		BoomMissile();

	}

}

void AMissile_Apache::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}

void AMissile_Apache::MissileMove(FVector TargetLoc)
{
	TargetLocation = TargetLoc;

	EngineOn = true;

}

void AMissile_Apache::BoomMissile()
{

	TArray<AActor*> OverlappingActors;
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	TArray<AActor*> ActorsToIgnore;

	// 폭발 범위
	UKismetSystemLibrary::CapsuleOverlapActors(GetWorld(), // 월드 컨텍스트 객체
		GetActorLocation(), // Capsule의 위치
		2000.f, // Capsule의 반지름
		2000.f, // Capsule의 반 높이
		ObjectTypes, // 충돌 허용 객체 유형
		nullptr, // 액터 클래스 필터
		ActorsToIgnore, // 무시할 액터들의 배열
		OverlappingActors // 결과를 저장할 배열
	);

	// 이펙트 연출
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), NSBoom, GetActorLocation(), FRotator(0), FVector(7));

	DrawDebugCapsule(GetWorld(), GetActorLocation(), 2000.f, 2000.f, FQuat::Identity, FColor::Blue, false, 30.0f, 0, 2.0f);

	// 미사일 폭발 사운드
	Start_BoomSound();

	// 공격기능
	if (OverlappingActors.Num() > 0) {
		for (AActor* Actor : OverlappingActors) {

			if (Actor->IsA<ATankBase>()) {

				// StateComponent를 이용해 체력을 감소시키는 방식으로 수정

				Actor->Destroy();

			}
			else if (Actor->IsA<ABunker>()) {
				Actor->Destroy();
			}

		}
	}

	Destroy();

}

void AMissile_Apache::SetInitialLocation()
{
	InitialLocation = GetActorLocation();
}

void AMissile_Apache::Start_FlyingSound()
{

	if (!FlyingSound) {
		return;
	}

	// 총알 소리 
	UGameplayStatics::PlaySoundAtLocation(
		GetWorld(),
		FlyingSound,		// Sound
		GetActorLocation(),   // Location
		GetActorRotation()	// Rotation
	);

}

void AMissile_Apache::Start_BoomSound()
{
	if (!BoomSound) {
		return;
	}

	// 총알 소리 
	UGameplayStatics::PlaySoundAtLocation(
		GetWorld(),
		BoomSound,			// Sound
		GetActorLocation(),   // Location
		GetActorRotation()  // Rotation
	);

}


void AMissile_Apache::SaveOwner()
{
	Apache = Cast<AHelicopter_Apache>(GetOwner());

}
