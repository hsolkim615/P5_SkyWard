// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../Component/HeliComp/HeliCompBase.h"
#include "HeliSoundComp.generated.h"

/**
 * 
 */
UCLASS()
class SKYWARD_API UHeliSoundComp : public UHeliCompBase
{
	GENERATED_BODY()
	
public:
	UHeliSoundComp();


	virtual void BeginPlay() override;


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USoundBase* HeliSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UAudioComponent* HeliSoundComp;

public:
	
	void PlayHeliSound_Engine();
	
};
