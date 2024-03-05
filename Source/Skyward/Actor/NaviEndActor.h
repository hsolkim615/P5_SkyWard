// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Actor/NaviLineActor.h"
#include "NaviEndActor.generated.h"

/**
 * 
 */
UCLASS()
class SKYWARD_API ANaviEndActor : public ANaviLineActor
{
	GENERATED_BODY()
	
public:
	ANaviEndActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void LengthFromHeli();

};
