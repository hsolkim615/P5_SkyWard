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
	ASkywardGameModeBase();

public:
	void Tick(float DeltaSeconds) override;

public:
	FTimerHandle GameTimerHandle;
	bool bIsTimerSet = false;

public:
	// ÆÄ±«µÈ ÅÊÅ© ¼ö
	int DestroyMoveTank = 0;
	int DestroyFixTank = 0;
	int DestroyTurret = 0;

	// ÆÄ±«µÈ °Ç¹° ¼ö
	int DestroyEnemyBuliding = 0;

	// Çï¸®Æ÷Æ®¿¡ Âø·ú
	bool bIsSuccess = false;

	bool bIsFail = false;

public:
	void ChangeLevel();


};
