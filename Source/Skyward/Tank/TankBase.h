// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Vehicle/VehicleBase.h"
#include "../Interface/StateInterface.h"
#include "TankBase.generated.h"

/**
 *
 */
UCLASS()
class SKYWARD_API ATankBase : public AVehicleBase, public IStateInterface
{
	GENERATED_BODY()

public:
	ATankBase();

public:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

protected:

	UFUNCTION()
	virtual void OnSeePawn(APawn* OtherPawn);

	void AimingPlayer();

	virtual void SpawnBullet();

	virtual void SetupTimer();

	void ResetDetection();

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float InterpSpeed = 1.0f;

	UPROPERTY()
	float bTimer = false;

	UPROPERTY()
	float Alpha = 0.1f;

	UPROPERTY()
	float ProjectileSpeed = 20000;

	UPROPERTY()
	float CurrentTime = 0;

	UPROPERTY()
	float AimingTime = 5.0f;

	UPROPERTY()
	float Interval = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Direction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTimerHandle TimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class ABullet_Tank> BulletClass;

	UPROPERTY()
	class AHelicopterBase* Player;

	UPROPERTY(EditAnywhere)
	class UPawnSensingComponent* pawnSensing;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStateComponent* StateComponent;

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UNiagaraComponent* NiagaraComp;*/

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//class UNiagaraSystem* Flame_Fire;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//class USoundWave* FireSound;



	// 게임모드 베이스
	class ASkywardGameModeBase* SkywardGM;


    void Damaged() override;
    void Die() override;
};



