// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Tank/TankBase.h"
#include "MachinegunTank.generated.h"

/**
 *
 */
UCLASS()
class SKYWARD_API AMachinegunTank : public ATankBase
{
	GENERATED_BODY()

public:
	AMachinegunTank();

public:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

public:

	//// 총알 발사 간격
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Machine_Interval = 0.1f;

	//// 타이머 핸들
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//FTimerHandle TimerHandle;

	// 발사 횟수 제한
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 NumBulletsToShoot = 20; // 5발 발사

	// 발사 횟수 카운트
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 NumBulletsShot = 0;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//TSubclassOf<class ABullet_Tank> ActorClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UNiagaraSystem* FireEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USoundWave* FireSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Mesh")
	class USkeletalMesh* NewMesh;

	void SpawnBullet() override;

	void Spawn();

	//void SetupTimer() override;



	void Damaged() override;
	void Die() override;
};
