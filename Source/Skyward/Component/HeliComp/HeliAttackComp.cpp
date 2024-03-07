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


	// �̻��� ���� �� ���� ==================================================================
	for (int i = 0; i < 8; i++) {

		// ���� �̸�
		FString SocketName = FString::Printf(TEXT("Missile_%d"), i);
		FName AttachmentSocketName(*SocketName);

		// �Ѿ��� �����ϴ� ���
		AMissile_Apache* SpawnMissile = GetWorld()->SpawnActor<AMissile_Apache>(MissileFactory_Apache, Apache->MGNozzleComp->GetComponentLocation(), Apache->MGNozzleComp->GetComponentRotation());

		SpawnMissile->SetOwner(Apache);
		SpawnMissile->SaveOwner();


		FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, false);

		SpawnMissile->AttachToComponent(Apache->GetMesh(), AttachmentRules, AttachmentSocketName);

		Missiles.Add(SpawnMissile);

	}
	// �̻��� ���� �� ���� ==================================================================

	// ����� �̻��� ���� �� ���� ===========================================================
	for (int i = 0; i < 76; i++) {

		// ���� �̸�
		FString SocketName = FString::Printf(TEXT("HydraMissile_%d"), i);
		FName AttachmentSocketName(*SocketName);

		// �Ѿ��� �����ϴ� ���
		AHydraMissile_Apache* SpawnHydraMissile = GetWorld()->SpawnActor<AHydraMissile_Apache>(HydraMissileFactory_Apache, Apache->MGNozzleComp->GetComponentLocation(), Apache->MGNozzleComp->GetComponentRotation());

		SpawnHydraMissile->SetOwner(Apache);
		SpawnHydraMissile->SaveOwner();


		FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, false);

		SpawnHydraMissile->AttachToComponent(Apache->GetMesh(), AttachmentRules, AttachmentSocketName);

		HydraMissile.Add(SpawnHydraMissile);

	}
	// ����� �̻��� ���� �� ���� ===========================================================

	// ��ź ���� ǥ�� ����
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

	// Ű���� ���ε�
	if (EnhancedInputComponent) {

		// �����
		EnhancedInputComponent->BindAction(IA_Heli_MachineGunShoot, ETriggerEvent::Triggered, this, &UHeliAttackComp::Shoot_MachineGun);
		EnhancedInputComponent->BindAction(IA_Heli_MachineGunShoot, ETriggerEvent::Completed, this, &UHeliAttackComp::Stop_MGEffect);

		// �� ���̾� �̻���
		EnhancedInputComponent->BindAction(IA_Heli_MissileShoot, ETriggerEvent::Started, this, &UHeliAttackComp::Shoot_Missile);

		// ����� �̻���
		EnhancedInputComponent->BindAction(IA_Heli_HydraMissileShoot, ETriggerEvent::Triggered, this, &UHeliAttackComp::Shoot_HydraMissile);

		// ����
		EnhancedInputComponent->BindAction(IA_Heli_Aming, ETriggerEvent::Triggered, this, &UHeliAttackComp::Shoot_Aming);

	}

}

// ����� ======================================================================================================================

void UHeliAttackComp::Shoot_MachineGun(const FInputActionValue& value)
{
	bool bIsValue = value.Get<bool>();

	if (Apache->BulletNumber <= 0) {
		return;
	}

	// Ÿ�̸Ӱ� �̹� Ȱ��ȭ�Ǿ� �ִٸ� �ߺ����� Ÿ�̸Ӹ� �������� ����
	if (!GetWorld()->GetTimerManager().IsTimerActive(MGTimerHandle))
	{
		// ���� �ð����� SpawnBullet �Լ��� ȣ��
		GetWorld()->GetTimerManager().SetTimer(MGTimerHandle, this, &UHeliAttackComp::SpwanBullet, 0.05f, false);
	}

	Start_MGEffect();

}

void UHeliAttackComp::SpwanBullet()
{
	// �Ѿ� ����
	ABullet_Apache* SpawnBullet = GetWorld()->SpawnActor<ABullet_Apache>(BulletFactory_Apache, Apache->MGNozzleComp->GetComponentLocation(), Apache->MGNozzleComp->GetComponentRotation());

	// �Ѿ� ��
	Apache->BulletNumber -= 1;

	// ������ �Ѿ��� ���� ����
	SpawnBullet->SetOwner(Apache);
	SpawnBullet->SaveOwner();

	// �Ѿ� �߻�
	if (bIsHit) {
		SpawnBullet->BulletMove(HitResult.Location);

	}
	else if (!bIsHit) {
		SpawnBullet->BulletMove(EndLocation);

	}

	// �Ѿ� �Ҹ�
	Start_MGSound();

}

void UHeliAttackComp::Start_MGSound()
{
	// �Ѿ� �Ҹ� 
	UGameplayStatics::PlaySoundAtLocation(
		GetWorld(),
		BulletSound,									// Sound
		Apache->MGNozzleComp->GetComponentLocation(),   // Location
		Apache->MGNozzleComp->GetComponentRotation()	// Rotation
	);

}

void UHeliAttackComp::Start_MGEffect()
{
	// �ѿ��� �Ҳ� ����Ʈ ����
	Apache->MGEffectComp->SetActive(true);

}

void UHeliAttackComp::Stop_MGEffect(const FInputActionValue& value)
{
	bool bIsValue = value.Get<bool>();

	// �ѿ��� �Ҳ� ����Ʈ ����
	Apache->MGEffectComp->SetActive(false);

}

// ����� ======================================================================================================================
// �̻��� ======================================================================================================================

void UHeliAttackComp::Shoot_Missile(const FInputActionValue& value)
{
	bool bIsValue = value.Get<bool>();

	// �̻����� ������ �Լ� ��
	if (Apache->MissileNumber <= 0 || Missiles.Num() == 0) {
		return;
	}

	// �迭 0�� �̻����� CurrentMissile �� ���� - �߻��� �̻���
	AMissile_Apache* CurrentMissile = Missiles[0];

	CurrentMissile->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	CurrentMissile->NSComp->SetActive(true);

	// �̻��� ��
	Apache->MissileNumber -= 1;

	// �̻��� �߻�
	if (bIsHit) {
		CurrentMissile->SetInitialLocation();
		CurrentMissile->MissileMove(HitResult.Location);

	}
	else if (!bIsHit) {
		CurrentMissile->SetInitialLocation();
		CurrentMissile->MissileMove(EndLocation);

	}

	CurrentMissile->Start_FlyingSound();

	// �߻��� �̻����� �迭���� ����
	if (Missiles.Num() > 0) {
		Missiles.Remove(CurrentMissile);
	}

}

void UHeliAttackComp::Shoot_HydraMissile(const FInputActionValue& value)
{

	bool bIsValue = value.Get<bool>();

	// �̻����� ������ �Լ� ��
	if (Apache->HydraMissileNumber <= 0 || HydraMissile.Num() == 0) {
		return;
	}

	// Ÿ�̸Ӱ� �̹� Ȱ��ȭ�Ǿ� �ִٸ� �ߺ����� Ÿ�̸Ӹ� �������� ����
	if (!GetWorld()->GetTimerManager().IsTimerActive(HydraTimerHandle))
	{
		// ���� �ð����� SpawnBullet �Լ��� ȣ��
		GetWorld()->GetTimerManager().SetTimer(HydraTimerHandle, this, &UHeliAttackComp::SetHydraMissile, 0.5f, false);
	}

}

void UHeliAttackComp::SetHydraMissile()
{
	// �迭 0�� �̻����� CurrentMissile �� ���� - �߻��� �̻���
	AHydraMissile_Apache* CurrentHydraMissile = HydraMissile[0];

	CurrentHydraMissile->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	CurrentHydraMissile->NSComp->SetActive(true);

	// �̻��� ��
	Apache->HydraMissileNumber -= 1;

	// �̻��� �߻�
	if (bIsHit) {
		CurrentHydraMissile->SetInitialLocation();
		CurrentHydraMissile->MissileMove(HitResult.Location);

	}
	else if (!bIsHit) {
		CurrentHydraMissile->SetInitialLocation();
		CurrentHydraMissile->MissileMove(EndLocation);

	}

	// �߻��� �̻����� �迭���� ����
	if (HydraMissile.Num() > 0) {
		HydraMissile.Remove(CurrentHydraMissile);
	}
}

// �̻��� ======================================================================================================================

void UHeliAttackComp::Shoot_Aming(const FInputActionValue& value)
{
	FVector2D bIsValue = value.Get<FVector2D >();


}

void UHeliAttackComp::AmingMark()
{

	/*
	// ���� ��ġ�� �� ��ġ�� ��� �����ؾ� �� - tick
	StartLocation = Apache->CameraLocComp->GetComponentLocation();// ���� ��ġ ����
	EndLocation = StartLocation + (Apache->CameraLocComp->GetForwardVector() * AttackRange); // ���� ��ġ ����
	*/

	// vr���¿� ���� �������� �����ϵ��� CameraComp�� ��ġ�� ���
	StartLocation = Apache->CameraComp->GetComponentLocation();// ���� ��ġ ����
	EndLocation = StartLocation + (Apache->CameraComp->GetForwardVector() * AttackRange); // ���� ��ġ ����


	// ������ ���� ����
	CollisionParams.AddIgnoredActor(Cast<AActor>(Apache)); // this�� ���� ������ �����͸� ��Ÿ���ϴ�.

	// ���� Ʈ���̽� ����
	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, TraceChannel, CollisionParams))
	{
		bIsHit = true;

		MarkActor->SetActorLocation(HitResult.Location);

		// MarkActor�� �������� �����ϴ� ���
		// ���� ��ġ�� �� ��ġ ������ �Ÿ� ���
		float TraceDistance = FVector::Distance(StartLocation, HitResult.Location);

		// �Ÿ��� ����� MarkActor�� ������ ����
		float ScaleFactor = FMath::GetMappedRangeValueClamped(FVector2D(0.f, AttackRange), FVector2D(1.f, 100.f), TraceDistance);

		MarkActor->SetActorScale3D(FVector(ScaleFactor));

	}
	else
	{
		bIsHit = false;

		MarkActor->SetActorLocation(EndLocation);

		// MarkActor�� �������� �����ϴ� ���
		// ���� ��ġ�� �� ��ġ ������ �Ÿ� ���
		float TraceDistance = FVector::Distance(StartLocation, EndLocation);

		// �Ÿ��� ����� MarkActor�� ������ ����
		float ScaleFactor = FMath::GetMappedRangeValueClamped(FVector2D(0.f, AttackRange), FVector2D(1.f, 100.f), TraceDistance);

		MarkActor->SetActorScale3D(FVector(ScaleFactor));

	}



}
