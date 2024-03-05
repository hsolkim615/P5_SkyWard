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


	/*
	UPROPERTY()
	float Interval = 5.0f;*/

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//FTimerHandle TimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UNiagaraSystem* FireEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USoundWave* FireSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Mesh")
	class USkeletalMesh* NewMesh;

	void SpawnBullet() override;

	//void SetupTimer() override;


	



	void Damaged() override;
	void Die() override;
};

