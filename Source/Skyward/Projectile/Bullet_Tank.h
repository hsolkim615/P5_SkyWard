// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet_Tank.generated.h"

UCLASS()
class SKYWARD_API ABullet_Tank : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABullet_Tank();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	UPROPERTY()
	class AHelicopterBase* Player;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USphereComponent* CollisionComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* meshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UProjectileMovementComponent* MovementComp;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//class UNiagaraSystem* Flame_Damage;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UNiagaraSystem* BulletFlame;


	//float MaxDistance = 1000.0f; // 초기 속도가 최대가 될 거리
	//float MinSpeed = 5000.0f; // 초기 속도의 최소값
	//float MaxSpeed = 10000.0f; // 초기 속도의 최대값
	
	float DelayInSeconds = 8.0f;

	void NotifyActorBeginOverlap(AActor* OtherActor) override;
	void BulletDestroy();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AttackDamage = 0;

};
