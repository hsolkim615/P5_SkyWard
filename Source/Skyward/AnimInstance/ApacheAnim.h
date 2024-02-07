// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <../Plugins/Experimental/ChaosVehiclesPlugin/Source/ChaosVehicles/Public/VehicleAnimationInstance.h>
#include "ApacheAnim.generated.h"

/**
 * 
 */
UCLASS()
class SKYWARD_API UApacheAnim : public UVehicleAnimationInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeBeginPlay() override;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

public:
	UPROPERTY()
	class AHelicopter_Apache* Owner_Apache;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ABP_MainRoter_Z_Yaw;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ABP_RPM;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ABP_RearRotator_Y_Pitch;




};
