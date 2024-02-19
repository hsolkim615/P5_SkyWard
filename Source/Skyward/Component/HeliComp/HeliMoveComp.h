// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../Component/HeliComp/HeliCompBase.h"
#include <InputActionValue.h>
#include "HeliMoveComp.generated.h"

/**
 *
 */
//UCLASS( ClassGroup=(Helicopter_Apache), meta=(BlueprintSpawnableComponent) )

UCLASS()
class SKYWARD_API UHeliMoveComp : public UHeliCompBase
{
	GENERATED_BODY()

public:
	UHeliMoveComp();

public:
	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void SetupPlayerInput(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|HeliKey")
	class UInputAction* IA_Apache_Cyclic;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|HeliKey")
	class UInputAction* IA_Apache_Collective;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|HeliKey")
	class UInputAction* IA_Apache_Pedal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|HeliKey")
	class UInputAction* IA_Apache_Throttle;

public: // Heli - Moving 
	void Cyclie_RightThumbStick(const FInputActionValue& value);
	void UpdateHelicopterAngle(const FVector2D& InputValue);
	void StopUpdatingHelicopterAngle();

	void Collective_LeftGrip(const FInputActionValue& value);

	void Pedal_Trigger(const FInputActionValue& value);

	// ��� �õ�
	void On_Off_Function(const FInputActionValue& value);

public:
	// ������ ���
	void HoldHeliAltitude();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ActionValueUpDown;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ApacheAltitude;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MainRotorSpeedRate;
	

	



	bool bIsEngineOnOff = false;







	// �α׿� ����
	float CurrentPitch;
	float CurrentRoll;
};
