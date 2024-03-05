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
	// 기관총 발사
	void Shoot_MachineGun(const FInputActionValue& value);
	void SpwanBullet();
	void Start_MGSound();
	void Start_MGEffect();
	void Stop_MGEffect(const FInputActionValue& value);

	// 미사일 발사
	void Shoot_Missile(const FInputActionValue& value);

	// 히드라 미사일 발사
	void Shoot_HydraMissile(const FInputActionValue& value);


	void Shoot_Aming(const FInputActionValue& value);

	void AmingMark();


public:
	// 총알 공장
	UPROPERTY(EditAnywhere, Category = Spawn_Projectile)
	TSubclassOf<class ABullet_Apache> BulletFactory_Apache;

	// 미사일 공장
	UPROPERTY(EditAnywhere, Category = Spawn_Projectile)
	TSubclassOf<class AMissile_Apache> MissileFactory_Apache;

	// 히드라 미사일 공장
	UPROPERTY(EditAnywhere, Category = Spawn_Projectile)
	TSubclassOf<class AHydraMissile_Apache> HydraMissileFactory_Apache;

	// 헬기가 갖고 있는 미사일들 저장하는 배열
	TArray<class AMissile_Apache*> Missiles;

	// 헬기가 갖고 있는 히드라 미사일들 저장하는 배열
	TArray<class AHydraMissile_Apache*> HydraMissile;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sound", meta = (AllowPrivateAccess = "true"))
	class USoundBase* BulletSound;

public:
	// 타이머 핸들
	FTimerHandle TimerHandle;


	// 라인트레이스 ----------
	FHitResult HitResult;
	float AttackRange = 800000.f; // 사정거리
	FVector StartLocation;// 시작 위치 설정
	FVector EndLocation; // 종료 위치 설정
	ECollisionChannel TraceChannel = ECollisionChannel::ECC_Visibility; // 라인 트레이스할 채널 설정
	FCollisionQueryParams CollisionParams; // 무시할 액터

	bool bIsHit = false;

	// 미사일 공장
	UPROPERTY(EditAnywhere, Category = Spawn_Projectile)
	TSubclassOf<class AActor> MarkFactory;

	UPROPERTY(EditAnywhere, Category = Spawn_Projectile)
	class AActor* MarkActor;

};
