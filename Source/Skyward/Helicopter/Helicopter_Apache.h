// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Helicopter/HelicopterBase.h"
#include "InputActionValue.h"
#include "../Interface/StateInterface.h"
#include "Helicopter_Apache.generated.h"

/**
 *
 */

 // UInputComponent를 매개변수로 하는 델리게이트
DECLARE_MULTICAST_DELEGATE_OneParam(FInputDelegate, class UInputComponent*);

UCLASS()
class SKYWARD_API AHelicopter_Apache : public AHelicopterBase, public IStateInterface
{
	GENERATED_BODY()

public:
	AHelicopter_Apache();

public:
	FInputDelegate OnSetupInputDelegate;

public:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void PossessedBy(AController* NewController) override;

	virtual void UnPossessed() override;



public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Components")
	class UMotionControllerComponent* RightController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Components")
	class UMotionControllerComponent* LeftController;


public:
	// 키 바인딩
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// IMC 맵핑
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Components")
	class UInputMappingContext* IMC_Heli;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* DoorCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USceneComponent* MGNozzleComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UParticleSystemComponent* MGEffectComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USceneComponent* CameraLocComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCameraComponent* CameraComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UWidgetComponent* HeliInfoUIComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UWidgetComponent* MissionUIComp;

public: // Actor Comp
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UHeliCompBase* MoveComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UHeliCompBase* AttackComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UHeliCompBase* SoundComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UHeliCompBase* SystemComp;



	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UWidgetComponent* GameEndUI1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UWidgetComponent* GameEndUI2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UWidgetComponent* GameEndUI3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UWidgetComponent* GameEndUI4;



	// Test 컴포넌트
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UHeliCompBase* TestComp;



public:	// MoveComp
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MainRotorSpeed_Apache = 0;

	bool bIsOpenDoor = true;

	int32 BulletNumber = 1200;
	int32 MissileNumber = 8;
	int32 HydraMissileNumber = 76;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Components")
	class UInputAction* IA_TakeHeli_RightA;

public:
	class ASkywardGameModeBase* SkywardGM;

public:
	/*
		UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	*/
	class AActor* HeliOtherActor;

public:
	void ModifyMapping(bool bAddMapping);

public:
	void SetDoor();

	
public: // 사운드
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USoundBase* WinSound;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USoundBase* LoseSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USoundBase* OpenSound;



public: // 인터페이스 함수
	// 피가 절반 이하일 때
	void Damaged() override;

	// 피가 0 이하 일 때
	void Die() override;

};
