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
	// UPROPERTY(EditAnywhere)
	// class UBoxComponent* boxComp;
	//
	// UPROPERTY(EditAnywhere)
	// class UStaticMeshComponent* meshComp;

public:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;


public:

	UPROPERTY(BlueprintReadOnly)
	class UTankFSM* FSM;

	//UPROPERTY(EditAnywhere)
	//float AttackRange;

	//UPROPERTY(EditAnywhere)
	//float AttackRange;

	//UPROPERTY(EditAnywhere)
	//float MaxHp;

	//UPROPERTY(EditAnywhere)
	//float CurrentHp;

	//UPROPERTY(EditAnywhere)
	//float AttackTime;

	//UPROPERTY()
	//class AHelicopterBase* Player;

	//UPROPERTY()
	//class ATankBase* Me;

	//UPROPERTY()
	//void Attack();

	//UPROPERTY()
	//void Damage(Param);

	//UPROPERTY()
	//void Die();

	//UPROPERTY()
	//void DrawTrajectory();
};


	
