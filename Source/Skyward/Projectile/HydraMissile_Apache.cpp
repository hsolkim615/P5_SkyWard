// Fill out your copyright notice in the Description page of Project Settings.


#include "../Projectile/HydraMissile_Apache.h"
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
#include "Missile_Apache.h"

AHydraMissile_Apache::AHydraMissile_Apache()
{

	PrimaryActorTick.bCanEverTick = true;

	HitCollision = CreateDefaultSubobject<USphereComponent>(TEXT("HitCollision"));
	SetRootComponent(HitCollision);
	HitCollision->SetSphereRadius(10.f);

	// �Ѿ� ����
	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(RootComponent);
	MeshComp->SetRelativeLocation(FVector(-40, 0, 0));

	NSComp = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NSComp"));
	NSComp->SetupAttachment(RootComponent);
	NSComp->SetRelativeLocation(FVector(-120, 0, 0));

}

void AHydraMissile_Apache::BeginPlay()
{
	Super::BeginPlay();


	// HitCollision�� overlap�Ǿ��� �� ȣ��
	HitCollision->OnComponentBeginOverlap.AddDynamic(this, &AHydraMissile_Apache::OnOverlapBegin);

	NSComp->SetActive(false);

}

void AHydraMissile_Apache::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (EngineOn == false) {
		return;
	}

	// ��ǥ ��ġ�� �ε巴�� �̵�
	FVector CurrentLocation = GetActorLocation();
	FVector Direction = (TargetLocation - CurrentLocation).GetSafeNormal();
	FVector NewLocation = CurrentLocation + Direction * CurrentSpeed * DeltaTime;
	SetActorLocation(NewLocation);

	
	if (FVector::Distance(GetActorLocation(), TargetLocation) <= 100) {
		BoomMissile();
	}
	

}

void AHydraMissile_Apache::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	
	if (!OtherActor->IsA<AHelicopter_Apache>() && !OtherActor->IsA<AMissile_Apache>() && !OtherActor->IsA<AHydraMissile_Apache>()) {
		BoomMissile();

	}
	

}

void AHydraMissile_Apache::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}

void AHydraMissile_Apache::MissileMove(FVector TargetLoc)
{
	TargetLocation = TargetLoc;

	EngineOn = true;
}

void AHydraMissile_Apache::BoomMissile()
{
	TArray<AActor*> OverlappingActors;
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	TArray<AActor*> ActorsToIgnore;

	// ���� ����
	UKismetSystemLibrary::CapsuleOverlapActors(GetWorld(), // ���� ���ؽ�Ʈ ��ü
		GetActorLocation(), // Capsule�� ��ġ
		1000.f, // Capsule�� ������
		1000.f, // Capsule�� �� ����
		ObjectTypes, // �浹 ��� ��ü ����
		nullptr, // ���� Ŭ���� ����
		ActorsToIgnore, // ������ ���͵��� �迭
		OverlappingActors // ����� ������ �迭
	);

	// ����Ʈ ����
	//UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), NSBoom, GetActorLocation(), FRotator(0), FVector(7));

	DrawDebugCapsule(GetWorld(), GetActorLocation(), 2000.f, 2000.f, FQuat::Identity, FColor::Blue, false, 30.0f, 0, 2.0f);

	// �̻��� ���� ����
	//Start_BoomSound();

	// ���ݱ��
	if (OverlappingActors.Num() > 0) {
		for (AActor* Actor : OverlappingActors) {

			if (Actor->IsA<ATankBase>()) {

				// StateComponent�� �̿��� ü���� ���ҽ�Ű�� ������� ����

				Actor->Destroy();

			}
			else if (Actor->IsA<ABunker>()) {
				Actor->Destroy();
			}

		}
	}

	Destroy();
}

void AHydraMissile_Apache::SetInitialLocation()
{
	InitialLocation = GetActorLocation();

}

void AHydraMissile_Apache::Start_FlyingSound()
{
	if (!FlyingSound) {
		return;
	}

	// �Ѿ� �Ҹ� 
	UGameplayStatics::PlaySoundAtLocation(
		GetWorld(),
		FlyingSound,		// Sound
		GetActorLocation(),   // Location
		GetActorRotation()	// Rotation
	);
}

void AHydraMissile_Apache::Start_BoomSound()
{
	if (!BoomSound) {
		return;
	}

	// �Ѿ� �Ҹ� 
	UGameplayStatics::PlaySoundAtLocation(
		GetWorld(),
		BoomSound,			// Sound
		GetActorLocation(),   // Location
		GetActorRotation()  // Rotation
	);
}

void AHydraMissile_Apache::SaveOwner()
{
	Apache = Cast<AHelicopter_Apache>(GetOwner());

}
