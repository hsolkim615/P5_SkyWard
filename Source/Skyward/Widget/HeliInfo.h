// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HeliInfo.generated.h"

/**
 *
 */
UCLASS()
class SKYWARD_API UHeliInfo : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* txt_RollAngle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* txt_PitchAngle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* txt_Altitude;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* txt_Bullet;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* txt_Missile;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* txt_HydraMissile;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	class UProgressBar* HP_Bar;

public:
	UFUNCTION()
	void SetRollAngle();

	UFUNCTION()
	void SetPitchAngle();

	UFUNCTION()
	void SetAltitude();

	UFUNCTION()
	void SetBullet();

	UFUNCTION()
	void SetMissile();

	UFUNCTION()
	void SetHydraMissile();

public:
	class AHelicopter_Apache* Apache;

};
