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

	UPROPERTY()
	float Alpha = 0.5f;

	UPROPERTY(EditAnywhere)
	class UPawnSensingComponent* pawnSensing;

	UPROPERTY()
	class AHelicopterBase* Player;

protected:
    UFUNCTION()
	virtual void OnSeePawn(APawn* OtherPawn);


	
};

