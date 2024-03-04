// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../Component/HeliComp/HeliCompBase.h"
#include <InputActionValue.h>
#include "HeliSystemComp.generated.h"

/**
 *
 */
UCLASS()
class SKYWARD_API UHeliSystemComp : public UHeliCompBase
{
	GENERATED_BODY()

public:
	UHeliSystemComp();

public:
	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void SetupPlayerInput(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|HeliKey")
	class UInputAction* IA_Apache_Menu;

public:
	void MissionWidget();


};
