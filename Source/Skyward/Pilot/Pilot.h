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



public:
	// IMC ¸ÊÇÎ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|PilotKey")
	class UInputMappingContext* IMC_Pilot;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|PilotKey")
	class UInputAction* IA_Pilot_Move;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|PilotKey")
	class UInputAction* IA_Pilot_Turn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|PilotKey")
	class UInputAction* IA_Pilot_LineTrace;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|PilotKey")
	class UInputAction* IA_Pilot_TakeHeli;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCameraComponent* CameraComp;

public:
	void Pilot_Move(const FInputActionValue& value);

	void Pilot_Turn(const FInputActionValue& value);

	void Pilot_LineTrace(const FInputActionValue& value);

	void Pilot_TakeHeli(const FInputActionValue& value);


public:
	FVector PilotDirection;

	class AHelicopterBase* HeliActor;


public:
	void ModifyMapping(bool bAddMapping);


};
