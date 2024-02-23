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

	// 헬기 시동
	void Engine_On_Off(const FInputActionValue& value);

	// 운행 모드 바꾸기

	void ChangeDrivingMode(const FInputActionValue& value);

	// 고도 유지 모드
	void AltitudeHoldMode();

	// 호버링 모드
	void AutoHoveringMode();

public:
	// 고도유지 기능
	void HoldHeliAltitude();

public:
	// 상승, 하강 변수 = -1 / 0 / 1 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ActionValueUpDown;
	
	// 헬기 고도
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ApacheAltitude;

	// 프로펠라 회전
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MainRotorSpeedRate;
	

	


	// 엔진 시동 여부
	bool bIsEngineOnOff = false;

	// 헬기 고도 기준점
	float StandHigh = 0.f;

	// 최대 고도
	float MaxAltitude = 40000.f;

	// 로그용 변수
	float CurrentPitch;
	float CurrentRoll;
};
