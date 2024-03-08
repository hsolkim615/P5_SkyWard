// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MissionSystem.generated.h"

/**
 *
 */
UCLASS()
class SKYWARD_API UMissionSystem : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public: // 첫번째 미션
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* txt_Mission_First_Tank;

	UFUNCTION()
	void SetTankNumber();


public: // 두번째 미션
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* txt_Mission_Second_Buliding;

	UFUNCTION()
	void SetBuildingNumber();


public: // 세번째 미션


public: // 공용
	class ASkywardGameModeBase* SkywardGM;

	class AHelicopter_Apache* Apache;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	class UWidgetSwitcher* WidgetSwitcher;

	int TankNumber = 0;
	int BuildingNumber = 0;

	int WidgetIndexNum = 0;

public:
	UFUNCTION()
	void SwitchMission(int32 IndexNum);


public:
	
	int CurrentMisssionNumber = 0;
	
	
};
