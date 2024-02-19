// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Projectile/ProjectileBase.h"
#include "Bullet_Apache.generated.h"

/**
 * 
 */
UCLASS()
class SKYWARD_API ABullet_Apache : public AProjectileBase
{
	GENERATED_BODY()
	
public:
	ABullet_Apache();

public:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USphereComponent* HitCollision;
	
	/*
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UProjectileMovementComponent* MoveComp;
	*/


public:
	void BulletMove(FVector TargetLoc);

public:
	FVector TargetLocation;

};
