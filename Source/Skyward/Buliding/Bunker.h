// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Interface/StateInterface.h"
#include "Bunker.generated.h"

UCLASS()
class SKYWARD_API ABunker : public AActor, public IStateInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABunker();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	class UStateComponent* StateComponent;

public:
	// 게임모드 베이스
	class ASkywardGameModeBase* SkywardGM;

public: // 인터페이스 함수
	// 피가 절반 이하일 때
	void Damaged() override;

	// 피가 0 이하 일 때
	void Die() override;

};
