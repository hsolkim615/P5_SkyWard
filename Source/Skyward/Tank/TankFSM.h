// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankFSM.generated.h"

// UENUM(BlueprintType)
// enum class EEnemyState : uint8
// {
// 	Idle,
// 	Attack,
// 	Damage,
// 	Die,
// };


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SKYWARD_API UTankFSM : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankFSM();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	// UPROPERTY(BlueprintReadOnly, Category=FSM)
	// EEnemyState mState = EEnemyState::Attack;

	UPROPERTY()
	class AHelicopterBase* Player;

	UPROPERTY()
	class ATankBase* Me;
	
	
		
};
