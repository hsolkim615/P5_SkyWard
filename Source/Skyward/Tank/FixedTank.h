// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Tank/TankBase.h"
#include "FixedTank.generated.h"


/**
 * 
 */
UCLASS()
class SKYWARD_API AFixedTank : public ATankBase
{
	GENERATED_BODY()

public:
	AFixedTank();

public:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Direction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTimerHandle SpawnTimerHandle;

	UPROPERTY()
	float Alpha = 0.1f;

	UPROPERTY()
	float ProjectileSpeed = 20000;

	UPROPERTY(EditAnywhere)
	class UPawnSensingComponent* pawnSensing;

	UPROPERTY()
	class AHelicopterBase* Player;

protected:
    UFUNCTION()
	virtual void OnSeePawn(APawn* OtherPawn);

	void SpawnActorFunction();
	
	void SetupSpawnTimer();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class ABullet_Tank> ActorClass;
};

