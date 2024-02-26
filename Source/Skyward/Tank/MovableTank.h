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
	
	void FindPath(APath* path);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	APath* FoundActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MappedValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UChaosWheeledVehicleMovementComponent* ChaosWheeledVehicleMovementComponent;

	UPROPERTY()
	class AAIController* ai;

	//UFUNCTION()
	//void MoveTank();

	UPROPERTY()
	class ADestination* Dest;
};
