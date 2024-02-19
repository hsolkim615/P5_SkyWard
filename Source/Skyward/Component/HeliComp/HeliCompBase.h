// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HeliCompBase.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SKYWARD_API UHeliCompBase : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHeliCompBase();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	virtual void InitializeComponent() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void SetupPlayerInput(class UInputComponent* PlayerInputComponent);

	UPROPERTY()
	class AHelicopter_Apache* Apache;

	UPROPERTY()
	class UHeliMoveComp* HeliComp_Move;

	UPROPERTY()
	class UHeliAttackComp* HeliComp_Attack;

	UPROPERTY()
	class UHeliSoundComp* HeliComp_Sound;

};
