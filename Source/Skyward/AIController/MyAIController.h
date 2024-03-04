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
    // ������
    AMyAIController();

protected:
    // ������ �� ȣ���
    virtual void BeginPlay() override;

    // �� �����Ӹ��� ȣ���
    virtual void Tick(float DeltaSeconds) override;

private:
    // AI�� ��ǥ ��ġ
    FVector TargetLocation;

    // ��ǥ ��ġ�� �̵��ϱ� ���� ���� �Լ�
    void MoveToTargetLocation();

	
};


