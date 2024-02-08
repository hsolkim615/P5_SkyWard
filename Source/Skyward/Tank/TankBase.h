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
	UPROPERTY(BlueprintReadOnly)
	class UTankFSM* FSM;
};


	
