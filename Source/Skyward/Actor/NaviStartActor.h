// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Actor/NaviLineActor.h"
#include "NaviStartActor.generated.h"

/**
 * 
 */
UCLASS()
class SKYWARD_API ANaviStartActor : public ANaviLineActor
{
	GENERATED_BODY()
	
public:
	ANaviStartActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere)
	class ANaviEndActor* NaviEndActor;

	UPROPERTY(EditAnywhere, Category = Spawn_Actor)
	TSubclassOf<class AActor> NaviActorFactory;

	class AActor* SpawnNaviActor;

	TArray<class AActor*> linePositionActor;

public:
	void NaviLine(FVector P1, FVector P2, FVector P3);


};
