// Fill out your copyright notice in the Description page of Project Settings.


#include "../../Component/HeliComp/HeliAttackComp.h"
#include <EnhancedInputComponent.h>
#include "../../Helicopter/Helicopter_Apache.h"
#include "../../Projectile/Bullet_Apache.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Particles/ParticleSystemComponent.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Camera/CameraComponent.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h>

UHeliAttackComp::UHeliAttackComp()
{
	PrimaryComponentTick.bCanEverTick = true;


}

void UHeliAttackComp::BeginPlay()
{
	Super::BeginPlay();


}

void UHeliAttackComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


}

void UHeliAttackComp::SetupPlayerInput(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInput(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	// 키보드 바인딩
	if (EnhancedInputComponent) {

		EnhancedInputComponent->BindAction(IA_Heli_MachineGunShoot, ETriggerEvent::Triggered, this, &UHeliAttackComp::Shoot_MachineGun);
		EnhancedInputComponent->BindAction(IA_Heli_MachineGunShoot, ETriggerEvent::Completed, this, &UHeliAttackComp::Stop_MGEffect);


		EnhancedInputComponent->BindAction(IA_Heli_MachineGunShoot, ETriggerEvent::Started, this, &UHeliAttackComp::Shoot_MissileGun);

		EnhancedInputComponent->BindAction(IA_Heli_Aming, ETriggerEvent::Triggered, this, &UHeliAttackComp::Shoot_Aming);

	}

}

void UHeliAttackComp::Shoot_MachineGun(const FInputActionValue& value)
{
	bool bIsValue = value.Get<bool>();

	// 총알을 스폰하는 기능
	ABullet_Apache* SpawnBullet = GetWorld()->SpawnActor<ABullet_Apache>(BulletFactory_Apache, Apache->MGNozzleComp->GetComponentLocation(), Apache->MGNozzleComp->GetComponentRotation()/*Apache->GetMesh()->GetSocketRotation(FName("gun_tilt_jntSocket"))*/);

	// 총열에 불꽃 이펙트 스폰
	Apache->MGEffectComp->SetActive(true);

	FHitResult HitResult;
	float AttackRange = 50000.f; // 사정거리
	FVector StartLocation = Apache->CameraLocComp->GetComponentLocation()/* + FVector(-500,0,0)*/;// 시작 위치 설정
	FVector EndLocation = StartLocation + (Apache->CameraLocComp->GetForwardVector() * AttackRange); // 종료 위치 설정
	ECollisionChannel TraceChannel = ECollisionChannel::ECC_Visibility; // 라인 트레이스할 채널 설정
	FCollisionQueryParams CollisionParams; // 무시할 액터
	CollisionParams.AddIgnoredActor(Cast<AActor>(Apache)); // this는 현재 액터의 포인터를 나타냅니다.

	// 라인 트레이스 실행
	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, TraceChannel, CollisionParams))
	{
		//DrawDebugLine(GetWorld(), StartLocation, HitResult.ImpactPoint, FColor::Green, false, 5.0f, 0, 5.0f);
		
		SpawnBullet->BulletMove(HitResult.Location);

		//UE_LOG(LogTemp, Warning, TEXT("StartLocation: %s"), *StartLocation.ToString());
		//UE_LOG(LogTemp, Warning, TEXT("ImpactPoint: %s"), *HitResult.ImpactPoint.ToString());
		//UE_LOG(LogTemp, Warning, TEXT("EndLocation: %s"), *EndLocation.ToString());

	}
	else
	{
		//DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Green, false, 5.0f, 0, 5.0f);

		SpawnBullet->BulletMove(EndLocation);

	}

	// 발사 사운드 필요


}

void UHeliAttackComp::Stop_MGEffect(const FInputActionValue& value)
{
	bool bIsValue = value.Get<bool>();

	// 총열에 불꽃 이펙트 정지
	Apache->MGEffectComp->SetActive(false);

}

void UHeliAttackComp::Shoot_MissileGun(const FInputActionValue& value)
{
	bool bIsValue = value.Get<bool>();

}

void UHeliAttackComp::Shoot_Aming(const FInputActionValue& value)
{
	FVector2D bIsValue = value.Get<FVector2D >();


}
