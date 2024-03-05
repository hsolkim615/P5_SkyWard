// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SkywardGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SKYWARD_API ASkywardGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	// �ı��� ��ũ ��
	int DestroyMoveTank = 0;
	int DestroyFixTank = 0;
	int DestroyTurret = 0;

	// �ı��� �ǹ� ��
	int DestroyEnemyBuliding = 0;

public:
	void CountDestroyMoveTank();

};
