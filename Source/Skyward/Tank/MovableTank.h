// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Tank/TankBase.h"
#include "MovableTank.generated.h"

/**
 * 
 */
class APath;
UCLASS()
class SKYWARD_API AMovableTank : public ATankBase
{
	GENERATED_BODY()
	
public:
	AMovableTank();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


//	void OnSeePawn(APawn* OtherPawn) override;
	
	//void FindPath(APath* path);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	APath* FoundActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MappedValue;

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UChaosWheeledVehicleMovementComponent* ChaosWheeledVehicleMovementComponent;*/


	//UFUNCTION()
	//void MoveTank();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USplineComponent* Spline;

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class APath* Road;*/

	UPROPERTY()
	float SplineDist;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CheckGap = 500;

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USceneComponent* LP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USceneComponent* RP;*/

	/*UPROPERTY()
	class AAIController* ai;

	UPROPERTY()
	class ADestination* Dest;*/


	/*UPROPERTY()
	float Interval = 3.0f;*/

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTimerHandle TimerHandle;*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UNiagaraSystem* FireEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USoundWave* FireSound;

	void SpawnBullet() override;

	//void SetupTimer() override;

	void Damaged() override;
	void Die() override;
};
