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

	// 총알 발사 간격
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Interval = 0.2f; // 0.2초마다 발사

	// 타이머 핸들
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTimerHandle TimerHandle;

	// 발사 횟수 제한
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 NumBulletsToShoot = 5; // 5발 발사

	// 발사 횟수 카운트
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 NumBulletsShot = 0;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//TSubclassOf<class ABullet_Tank> ActorClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UNiagaraSystem* Flame_Fire;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USoundWave* FireSound;

	void SpawnBullet() override;

	void SetupTimer() override;
};
