// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MyAIController.generated.h"

/**
 * 
 */
UCLASS()
class SKYWARD_API AMyAIController : public AAIController
{
	GENERATED_BODY()

public:
    // 생성자
    AMyAIController();

protected:
    // 시작할 때 호출됨
    virtual void BeginPlay() override;

    // 매 프레임마다 호출됨
    virtual void Tick(float DeltaSeconds) override;

private:
    // AI의 목표 위치
    FVector TargetLocation;

    // 목표 위치로 이동하기 위한 내부 함수
    void MoveToTargetLocation();

	
};


