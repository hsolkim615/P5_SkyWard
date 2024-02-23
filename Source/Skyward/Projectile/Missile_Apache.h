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

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USphereComponent* HitCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USkeletalMeshComponent* MeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UNiagaraComponent* NSComp;

public:
	void MissileMove(FVector TargetLoc);

	void SaveOwner();

public:
	FVector TargetLocation;

	class AHelicopter_Apache* OwnerHeli;

	bool EngineOn = false;




public:
	// �̻����� ���ӵ�
	float MissileAcceleration = 3000.0f; // �̻����� ���ӵ�
	float MaxSpeed = 30000.0f; // �̻����� �ִ� �ӵ�
	float CurrentSpeed = 0.0f;

};
