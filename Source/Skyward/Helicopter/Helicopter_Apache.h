// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Helicopter/HelicopterBase.h"
#include "InputActionValue.h"
#include "Helicopter_Apache.generated.h"

/**
 * 
 */

 // UInputComponent�� �Ű������� �ϴ� ��������Ʈ
DECLARE_MULTICAST_DELEGATE_OneParam(FInputDelegate, class UInputComponent*);

UCLASS()
class SKYWARD_API AHelicopter_Apache : public AHelicopterBase
{
	GENERATED_BODY()

public:
	AHelicopter_Apache();

public:
	FInputDelegate OnSetupInputDelegate;

public:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;


public:
	// Ű ���ε�
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// IMC ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Components")
	class UInputMappingContext* IMC_Heli;

public: // Actor Comp
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UHeliCompBase* MoveComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UHeliCompBase* SoundComp;

public:	// MoveComp
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MainRotorSpeed = 0;


};
