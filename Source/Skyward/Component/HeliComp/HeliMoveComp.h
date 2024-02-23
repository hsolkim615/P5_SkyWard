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
	void Cyclic_RightThumbStick(const FInputActionValue& value);
	void UpdateHelicopterAngle(const FVector2D& InputValue);
	void StopUpdatingHelicopterAngle();

	void Collective_LeftGrip(const FInputActionValue& value);

	void Pedal_Trigger(const FInputActionValue& value);

	// ��� �õ�
	void Engine_On_Off(const FInputActionValue& value);

	// ���� ��� �ٲٱ�

	void ChangeDrivingMode(const FInputActionValue& value);

	// �� ���� ���
	void AltitudeHoldMode();

	// ȣ���� ���
	void AutoHoveringMode();

public:
	// ������ ���
	void HoldHeliAltitude();

public:
	// ���, �ϰ� ���� = -1 / 0 / 1 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ActionValueUpDown;
	
	// ��� ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ApacheAltitude;

	// ������� ȸ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MainRotorSpeedRate;
	

	


	// ���� �õ� ����
	bool bIsEngineOnOff = false;

	// ��� �� ������
	float StandHigh = 0.f;

	// �ִ� ��
	float MaxAltitude = 40000.f;

	// �α׿� ����
	float CurrentPitch;
	float CurrentRoll;
};
