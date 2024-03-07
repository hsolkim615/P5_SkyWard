// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameEndWidget.generated.h"

/**
 *
 */
UCLASS()
class SKYWARD_API UGameEndWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;



public: // °ø¿ë
	class ASkywardGameModeBase* SkywardGM;

	class AHelicopter_Apache* Apache;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	class UWidgetSwitcher* WidgetSwitcher;

};
