// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Projectile/ProjectileBase.h"
#include "HydraMissile_Apache.generated.h"

/**
 *
 */
UCLASS()
class SKYWARD_API AHydraMissile_Apache : public AProjectileBase
{
	GENERATED_BODY()

public:
	AHydraMissile_Apache();

public:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	void NotifyActorBeginOverlap(AActor* OtherActor) override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USphereComponent* HitCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USkeletalMeshComponent* MeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UNiagaraComponent* NSComp;

public:
	void MissileMove(FVector TargetLoc);

	void BoomMissile();

	void SetInitialLocation();

	void Start_FlyingSound();

	void Start_BoomSound();

	void SaveOwner();

public:
	FVector TargetLocation;

	class AHelicopter_Apache* Apache;

	bool EngineOn = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UNiagaraSystem* NSBoom;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USoundBase* FlyingSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USoundBase* BoomSound;

public:
	// 미사일의 가속도
	FVector InitialLocation;
	float CurrentSpeed = 100000.0f;


};
