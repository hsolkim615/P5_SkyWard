// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../Component/HeliComp/HeliCompBase.h"
#include <InputActionValue.h>
#include "HeliAttackComp.generated.h"

/**
 * 
 */
UCLASS()
class SKYWARD_API UHeliAttackComp : public UHeliCompBase
{
	GENERATED_BODY()

public:
	UHeliAttackComp();

public:
	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void SetupPlayerInput(class UInputComponent* PlayerInputComponent) override;

public: // InputAction
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|BindKey")
	class UInputAction* IA_Heli_MachineGunShoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|BindKey")
	class UInputAction* IA_Heli_MissileShoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|BindKey")
	class UInputAction* IA_Heli_Aming;

public:
	void Shoot_MachineGun(const FInputActionValue& value);
	void Stop_MGEffect(const FInputActionValue& value);

	void Shoot_MissileGun(const FInputActionValue& value);

	void Shoot_Aming(const FInputActionValue& value);

	UPROPERTY(EditAnywhere, Category = Spawn_ArrowType)
	TSubclassOf<class ABullet_Apache> BulletFactory_Apache;

};
