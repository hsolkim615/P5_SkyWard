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
	// InputAction
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|BindKey")
	class UInputAction* IA_Heli_FWD_BWD;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|BindKey")
	class UInputAction* IA_Heli_Up_Down;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|BindKey")
	class UInputAction* IA_Heli_Roll_Left_Right;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|BindKey")
	class UInputAction* IA_Heli_Steering;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|BindKey")
	class UInputAction* IA_Free_Look_Key;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|BindKey")
	class UInputAction* IA_Free_Look;

	// 엔진 시동
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|BindKey")
	class UInputAction* IA_On_Off;

public: // Heli - Moving
	void FWD_BWD_Function(const FInputActionValue& value);

	void Up_Down_Function(const FInputActionValue& value);

	void Roll_Left_Right_Function(const FInputActionValue& value);

	void Steering_Function(const FInputActionValue& value);

	void Free_Look_Key_Function(const FInputActionValue& value);

	void Free_Look_Function(const FInputActionValue& value);


	// 헬기 시동
	void On_Off_Function(const FInputActionValue& value);


public:
	void HoldHeliAltitude();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ActionValueUpDown;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ApacheAltitude;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MainRotorSpeedRate;
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Look_Function_VecterValue_Y;



	bool bIsEngineOnOff = false;

	TArray<class AActor*> IngnoreActors;


};
