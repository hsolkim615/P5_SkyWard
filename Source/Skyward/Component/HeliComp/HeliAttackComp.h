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
	class UInputAction* IA_Heli_HydraMissileShoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|BindKey")
	class UInputAction* IA_Heli_Aming;

public:
	// ����� �߻�
	void Shoot_MachineGun(const FInputActionValue& value);
	void SpwanBullet();
	void Start_MGSound();
	void Start_MGEffect();
	void Stop_MGEffect(const FInputActionValue& value);

	// �̻��� �߻�
	void Shoot_Missile(const FInputActionValue& value);

	// ����� �̻��� �߻�
	void Shoot_HydraMissile(const FInputActionValue& value);


	void Shoot_Aming(const FInputActionValue& value);

	void AmingMark();


public:
	// �Ѿ� ����
	UPROPERTY(EditAnywhere, Category = Spawn_Projectile)
	TSubclassOf<class ABullet_Apache> BulletFactory_Apache;

	// �̻��� ����
	UPROPERTY(EditAnywhere, Category = Spawn_Projectile)
	TSubclassOf<class AMissile_Apache> MissileFactory_Apache;

	// ����� �̻��� ����
	UPROPERTY(EditAnywhere, Category = Spawn_Projectile)
	TSubclassOf<class AHydraMissile_Apache> HydraMissileFactory_Apache;

	// ��Ⱑ ���� �ִ� �̻��ϵ� �����ϴ� �迭
	TArray<class AMissile_Apache*> Missiles;

	// ��Ⱑ ���� �ִ� ����� �̻��ϵ� �����ϴ� �迭
	TArray<class AHydraMissile_Apache*> HydraMissile;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sound", meta = (AllowPrivateAccess = "true"))
	class USoundBase* BulletSound;

public:
	// Ÿ�̸� �ڵ�
	FTimerHandle TimerHandle;


	// ����Ʈ���̽� ----------
	FHitResult HitResult;
	float AttackRange = 800000.f; // �����Ÿ�
	FVector StartLocation;// ���� ��ġ ����
	FVector EndLocation; // ���� ��ġ ����
	ECollisionChannel TraceChannel = ECollisionChannel::ECC_Visibility; // ���� Ʈ���̽��� ä�� ����
	FCollisionQueryParams CollisionParams; // ������ ����

	bool bIsHit = false;

	// �̻��� ����
	UPROPERTY(EditAnywhere, Category = Spawn_Projectile)
	TSubclassOf<class AActor> MarkFactory;

	UPROPERTY(EditAnywhere, Category = Spawn_Projectile)
	class AActor* MarkActor;

};
