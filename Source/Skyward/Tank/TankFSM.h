// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankFSM.generated.h"

 UENUM(BlueprintType)
 enum class EEnemyState : uint8
 {
 	Idle,
 	Attack,
 	Damage,
 	Die,
 };


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


	UPROPERTY(EditAnywhere)
	float AttackRange;

	UPROPERTY(EditAnywhere)
	float MaxHp;

	UPROPERTY(EditAnywhere)
	float CurrentHp;

	UPROPERTY(EditAnywhere)
	float AttackTime;

	UPROPERTY(EditAnywhere)
	float DeathTime;

	UPROPERTY(EditAnywhere)
	float CurrentTime = 0;

	UPROPERTY(BlueprintReadOnly, Category=FSM)
	EEnemyState mState = EEnemyState::Idle;

	UPROPERTY()
	class AHelicopterBase* Player;

	UPROPERTY()
	class ATankBase* Me;
		

private:
	void IdleState();
	void AttackState();
	void DieState();

public:
	void OnDamageProcess(int param);
};
