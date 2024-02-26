// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Vehicle/VehicleBase.h"
#include "TankBase.generated.h"

/**
 * 
 */
UCLASS()
class SKYWARD_API ATankBase : public AVehicleBase
{
	GENERATED_BODY()

public:
	ATankBase();
	
public:
	public:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	FVector Direction;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	FTimerHandle TimerHandle;
//
//	UPROPERTY()
//	float Alpha = 0.1f;
//
//	UPROPERTY()
//	float ProjectileSpeed = 20000;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	float InterpSpeed = 1.0f;
//
//	UPROPERTY()
//	float CurrentTime = 0;
//
//	UPROPERTY()
//	float AimingTime = 5.0f;
//
//	UPROPERTY()
//	float Interval = 3.0f;
//
//	UPROPERTY()
//	float bCanDetectPlayer = true;
//
//	UPROPERTY(EditAnywhere)
//	class UPawnSensingComponent* pawnSensing;
//
//	UPROPERTY()
//	class AHelicopterBase* Player;
//
//public:
//	//UFUNCTION()
//	virtual void OnSeePawn(APawn* OtherPawn);
//
//protected:
//
//	void SpawnBullet();
//	
//	void SetupTimer();
//
//	void AimingPlayer();
//
//	void ResetDetection();
//
//public:
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	TSubclassOf<class ABullet_Tank> ActorClass;
};


	
