// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <../../../../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/InputActionValue.h>
#include "Pilot.generated.h"

UCLASS()
class SKYWARD_API APilot : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APilot();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PossessedBy(AController* NewController) override;

	virtual void UnPossessed() override;



public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Components")
	class UMotionControllerComponent* RightController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Components")
	class UMotionControllerComponent* LeftController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Components")
	class USkeletalMeshComponent* RightHandMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Components")
	class USkeletalMeshComponent* LeftHandMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Components")
	class UWidgetInteractionComponent* RightWidgetInteractive;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Components")
	//class UWidgetInteractionComponent* LeftWidgetInteractive;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* ClickPointer;


public:
	// IMC 맵핑
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|PilotKey")
	class UInputMappingContext* IMC_Pilot;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|PilotKey")
	class UInputAction* IA_Pilot_Move;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|PilotKey")
	class UInputAction* IA_Pilot_Turn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|PilotKey")
	class UInputAction* IA_Pilot_Click;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|PilotKey")
	class UInputAction* IA_Pilot_TakeHeli;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCameraComponent* CameraComp;

public:
	void Pilot_Move(const FInputActionValue& value);

	void Pilot_Turn(const FInputActionValue& value);

	void Pilot_ClickPress(const FInputActionValue& value);

	void Pilot_ClickRelease(const FInputActionValue& value);


	//void Pilot_TakeHeli(const FInputActionValue& value);


public:
	FVector PilotDirection;

	//class AHelicopterBase* HeliActor;


public:
	void ModifyMapping(bool bAddMapping);

	void ClickLineTrace();


public:
	// 라인트레이스 ----------
	FHitResult HitResult;
	FVector StartLocation;// 시작 위치 설정
	FVector EndLocation; // 종료 위치 설정
	ECollisionChannel TraceChannel = ECollisionChannel::ECC_WorldDynamic; // 라인 트레이스할 채널 설정
	FCollisionQueryParams CollisionParams; // 무시할 액터



	// 미사일 공장
	UPROPERTY(EditAnywhere, Category = Spawn_Projectile)
	TSubclassOf<class AActor> ClickFactory;

	UPROPERTY(EditAnywhere, Category = Spawn_Projectile)
	class AActor* ClickActor;



};
