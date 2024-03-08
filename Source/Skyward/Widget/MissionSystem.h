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

public: // ù��° �̼�
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* txt_Mission_First_Tank;

	UFUNCTION()
	void SetTankNumber();


public: // �ι�° �̼�
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* txt_Mission_Second_Buliding;

	UFUNCTION()
	void SetBuildingNumber();


public: // ����° �̼�


public: // ����
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
