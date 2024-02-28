// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Projectile/ProjectileBase.h"
#include "Missile_Apache.generated.h"

/**
 *
 */
UCLASS()
class SKYWARD_API AMissile_Apache : public AProjectileBase
{
	GENERATED_BODY()

public:
	AMissile_Apache();

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

	void SaveOwner();

public:
	FVector TargetLocation;

	class AHelicopter_Apache* Apache;

	bool EngineOn = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UNiagaraSystem* NSBoom;


public:
	// 미사일의 가속도
	FVector InitialLocation;
	float MissileAcceleration = 3000.0f; // 미사일의 가속도
	float MaxSpeed = 50000.0f; // 미사일의 최대 속도
	float CurrentSpeed = 0.0f;

	//float InitialSpeed = 10;

public: // 공격기능

	bool bAttack = false;

	FHitResult HitResult;
	FVector StartLocation;// 시작 위치 설정
	FVector EndLocation; // 종료 위치 설정
	ECollisionChannel TraceChannel; // 라인 트레이스할 채널 설정
	FCollisionQueryParams CollisionParams; // 무시할 액터




};
