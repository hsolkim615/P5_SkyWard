// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StateComponent.generated.h"

UENUM()
enum class EState : uint8
{
	IDLE,
	DESTROY,
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SKYWARD_API UStateComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UStateComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	void SetMaxHealthPoint(float NewMaxHealthPoint);

	void SetHealthPoint(float NewHealthPoint);

	void SetAttackDamage(float NewAttackDamage);

	void TakeDamage(float Damage);

	void StateDestroy();

	UStateComponent* GetStateComponent();

public:

	UStateComponent* StateComponent;

	//VisibleInstanceOnly 
	// 체력
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float HealthPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxHealthPoint;

	// 공격력
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AttackDamage;

public: // Enum 
	EState GetEState() const;

	UPROPERTY(EditAnywhere)
	EState ActorState;
};
