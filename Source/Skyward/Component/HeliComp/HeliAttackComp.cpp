// Fill out your copyright notice in the Description page of Project Settings.


#include "../../Component/HeliComp/HeliAttackComp.h"
#include <EnhancedInputComponent.h>
#include "../../Helicopter/Helicopter_Apache.h"
#include "../../Projectile/Bullet_Apache.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Particles/ParticleSystemComponent.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Camera/CameraComponent.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h>
#include "../../Projectile/Missile_Apache.h"
#include <../../../../../../../Plugins/FX/Niagara/Source/Niagara/Public/NiagaraComponent.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Components/SceneComponent.h>
#include "../../Projectile/HydraMissile_Apache.h"

UHeliAttackComp::UHeliAttackComp()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UHeliAttackComp::BeginPlay()
{
	Super::BeginPlay();


	// 미사일 스폰 및 장착 ==================================================================
	for (int i = 0; i < 8; i++) {

		// 소켓 이름
		FString SocketName = FString::Printf(TEXT("Missile_%d"), i);
		FName AttachmentSocketName(*SocketName);

		// 총알을 스폰하는 기능
		AMissile_Apache* SpawnMissile = GetWorld()->SpawnActor<AMissile_Apache>(MissileFactory_Apache, Apache->MGNozzleComp->GetComponentLocation(), Apache->MGNozzleComp->GetComponentRotation());

		SpawnMissile->SetOwner(Apache);
		SpawnMissile->SaveOwner();


		FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, false);

		SpawnMissile->AttachToComponent(Apache->GetMesh(), AttachmentRules, AttachmentSocketName);

		Missiles.Add(SpawnMissile);

	}
	// 미사일 스폰 및 장착 ==================================================================

	// 히드라 미사일 스폰 및 장착 ===========================================================
	for (int i = 0; i < 76; i++) {

		// 소켓 이름
		FString SocketName = FString::Printf(TEXT("HydraMissile_%d"), i);
		FName AttachmentSocketName(*SocketName);

		// 총알을 스폰하는 기능
		AHydraMissile_Apache* SpawnHydraMissile = GetWorld()->SpawnActor<AHydraMissile_Apache>(HydraMissileFactory_Apache, Apache->MGNozzleComp->GetComponentLocation(), Apache->MGNozzleComp->GetComponentRotation());

		SpawnHydraMissile->SetOwner(Apache);
		SpawnHydraMissile->SaveOwner();


		FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, false);

		SpawnHydraMissile->AttachToComponent(Apache->GetMesh(), AttachmentRules, AttachmentSocketName);

		HydraMissile.Add(SpawnHydraMissile);

	}
	// 히드라 미사일 스폰 및 장착 ===========================================================

	// 착탄 지점 표시 액터
	if (MarkFactory) {
		MarkActor = GetWorld()->SpawnActor<AActor>(MarkFactory, HitResult.Location, FRotator(0));
	}

}

void UHeliAttackComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	AmingMark();

}

void UHeliAttackComp::SetupPlayerInput(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInput(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	// 키보드 바인딩
	if (EnhancedInputComponent) {

		// 기관총
		EnhancedInputComponent->BindAction(IA_Heli_MachineGunShoot, ETriggerEvent::Triggered, this, &UHeliAttackComp::Shoot_MachineGun);
		EnhancedInputComponent->BindAction(IA_Heli_MachineGunShoot, ETriggerEvent::Completed, this, &UHeliAttackComp::Stop_MGEffect);

		// 헬 파이어 미사일
		EnhancedInputComponent->BindAction(IA_Heli_MissileShoot, ETriggerEvent::Started, this, &UHeliAttackComp::Shoot_Missile);

		// 히드라 미사일
		EnhancedInputComponent->BindAction(IA_Heli_HydraMissileShoot, ETriggerEvent::Triggered, this, &UHeliAttackComp::Shoot_HydraMissile);

		// 조준
		EnhancedInputComponent->BindAction(IA_Heli_Aming, ETriggerEvent::Triggered, this, &UHeliAttackComp::Shoot_Aming);

	}

}

// 기관총 ======================================================================================================================

void UHeliAttackComp::Shoot_MachineGun(const FInputActionValue& value)
{
	bool bIsValue = value.Get<bool>();

	if (Apache->BulletNumber <= 0) {
		return;
	}

	// 타이머가 이미 활성화되어 있다면 중복으로 타이머를 시작하지 않음
	if (!GetWorld()->GetTimerManager().IsTimerActive(MGTimerHandle))
	{
		// 일정 시간마다 SpawnBullet 함수를 호출
		GetWorld()->GetTimerManager().SetTimer(MGTimerHandle, this, &UHeliAttackComp::SpwanBullet, 0.05f, false);
	}

	Start_MGEffect();

}

void UHeliAttackComp::SpwanBullet()
{
	// 총알 스폰
	ABullet_Apache* SpawnBullet = GetWorld()->SpawnActor<ABullet_Apache>(BulletFactory_Apache, Apache->MGNozzleComp->GetComponentLocation(), Apache->MGNozzleComp->GetComponentRotation());

	// 총알 수
	Apache->BulletNumber -= 1;

	// 스폰된 총알의 오너 설정
	SpawnBullet->SetOwner(Apache);
	SpawnBullet->SaveOwner();

	// 총알 발사
	if (bIsHit) {
		SpawnBullet->BulletMove(HitResult.Location);

	}
	else if (!bIsHit) {
		SpawnBullet->BulletMove(EndLocation);

	}

	// 총알 소리
	Start_MGSound();

}

void UHeliAttackComp::Start_MGSound()
{
	// 총알 소리 
	UGameplayStatics::PlaySoundAtLocation(
		GetWorld(),
		BulletSound,									// Sound
		Apache->MGNozzleComp->GetComponentLocation(),   // Location
		Apache->MGNozzleComp->GetComponentRotation()	// Rotation
	);

}

void UHeliAttackComp::Start_MGEffect()
{
	// 총열에 불꽃 이펙트 스폰
	Apache->MGEffectComp->SetActive(true);

}

void UHeliAttackComp::Stop_MGEffect(const FInputActionValue& value)
{
	bool bIsValue = value.Get<bool>();

	// 총열에 불꽃 이펙트 정지
	Apache->MGEffectComp->SetActive(false);

}

// 기관총 ======================================================================================================================
// 미사일 ======================================================================================================================

void UHeliAttackComp::Shoot_Missile(const FInputActionValue& value)
{
	bool bIsValue = value.Get<bool>();

	// 미사일이 없으면 함수 끝
	if (Apache->MissileNumber <= 0 || Missiles.Num() == 0) {
		return;
	}

	// 배열 0번 미사일을 CurrentMissile 에 저장 - 발사할 미사일
	AMissile_Apache* CurrentMissile = Missiles[0];

	CurrentMissile->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	CurrentMissile->NSComp->SetActive(true);

	// 미사일 수
	Apache->MissileNumber -= 1;

	// 미사일 발사
	if (bIsHit) {
		CurrentMissile->SetInitialLocation();
		CurrentMissile->MissileMove(HitResult.Location);

	}
	else if (!bIsHit) {
		CurrentMissile->SetInitialLocation();
		CurrentMissile->MissileMove(EndLocation);

	}

	CurrentMissile->Start_FlyingSound();

	// 발사한 미사일을 배열에서 제거
	if (Missiles.Num() > 0) {
		Missiles.Remove(CurrentMissile);
	}

}

void UHeliAttackComp::Shoot_HydraMissile(const FInputActionValue& value)
{

	bool bIsValue = value.Get<bool>();

	// 미사일이 없으면 함수 끝
	if (Apache->HydraMissileNumber <= 0 || HydraMissile.Num() == 0) {
		return;
	}

	// 타이머가 이미 활성화되어 있다면 중복으로 타이머를 시작하지 않음
	if (!GetWorld()->GetTimerManager().IsTimerActive(HydraTimerHandle))
	{
		// 일정 시간마다 SpawnBullet 함수를 호출
		GetWorld()->GetTimerManager().SetTimer(HydraTimerHandle, this, &UHeliAttackComp::SetHydraMissile, 0.5f, false);
	}

}

void UHeliAttackComp::SetHydraMissile()
{
	// 배열 0번 미사일을 CurrentMissile 에 저장 - 발사할 미사일
	AHydraMissile_Apache* CurrentHydraMissile = HydraMissile[0];

	CurrentHydraMissile->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	CurrentHydraMissile->NSComp->SetActive(true);

	// 미사일 수
	Apache->HydraMissileNumber -= 1;

	// 미사일 발사
	if (bIsHit) {
		CurrentHydraMissile->SetInitialLocation();
		CurrentHydraMissile->MissileMove(HitResult.Location);

	}
	else if (!bIsHit) {
		CurrentHydraMissile->SetInitialLocation();
		CurrentHydraMissile->MissileMove(EndLocation);

	}

	// 발사한 미사일을 배열에서 제거
	if (HydraMissile.Num() > 0) {
		HydraMissile.Remove(CurrentHydraMissile);
	}
}

// 미사일 ======================================================================================================================

void UHeliAttackComp::Shoot_Aming(const FInputActionValue& value)
{
	FVector2D bIsValue = value.Get<FVector2D >();


}

void UHeliAttackComp::AmingMark()
{

	/*
	// 시작 위치와 끝 위치는 계속 갱신해야 함 - tick
	StartLocation = Apache->CameraLocComp->GetComponentLocation();// 시작 위치 설정
	EndLocation = StartLocation + (Apache->CameraLocComp->GetForwardVector() * AttackRange); // 종료 위치 설정
	*/

	// vr헤드셋에 따라 조종간을 조종하도록 CameraComp의 위치를 사용
	StartLocation = Apache->CameraComp->GetComponentLocation();// 시작 위치 설정
	EndLocation = StartLocation + (Apache->CameraComp->GetForwardVector() * AttackRange); // 종료 위치 설정


	// 무시할 액터 저장
	CollisionParams.AddIgnoredActor(Cast<AActor>(Apache)); // this는 현재 액터의 포인터를 나타냅니다.

	// 라인 트레이스 실행
	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, TraceChannel, CollisionParams))
	{
		bIsHit = true;

		MarkActor->SetActorLocation(HitResult.Location);

		// MarkActor의 스케일을 조절하는 기능
		// 시작 위치와 끝 위치 사이의 거리 계산
		float TraceDistance = FVector::Distance(StartLocation, HitResult.Location);

		// 거리에 비례해 MarkActor의 스케일 조절
		float ScaleFactor = FMath::GetMappedRangeValueClamped(FVector2D(0.f, AttackRange), FVector2D(1.f, 100.f), TraceDistance);

		MarkActor->SetActorScale3D(FVector(ScaleFactor));

	}
	else
	{
		bIsHit = false;

		MarkActor->SetActorLocation(EndLocation);

		// MarkActor의 스케일을 조절하는 기능
		// 시작 위치와 끝 위치 사이의 거리 계산
		float TraceDistance = FVector::Distance(StartLocation, EndLocation);

		// 거리에 비례해 MarkActor의 스케일 조절
		float ScaleFactor = FMath::GetMappedRangeValueClamped(FVector2D(0.f, AttackRange), FVector2D(1.f, 100.f), TraceDistance);

		MarkActor->SetActorScale3D(FVector(ScaleFactor));

	}



}
