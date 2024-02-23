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

		FAttachmentTransformRules AttachmentRules(
			EAttachmentRule::SnapToTarget,
			EAttachmentRule::SnapToTarget,
			EAttachmentRule::KeepWorld,
			false
		);

		//SpawnMissile->AttachToComponent(Apache->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, AttachmentSocketName);
		SpawnMissile->AttachToComponent(Apache->GetMesh(), AttachmentRules, AttachmentSocketName);

		Missiles.Add(SpawnMissile);
	}
	// �̻��� ���� �� ���� ==================================================================


}

void UHeliAttackComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (Missiles.Num() > 0 && Missiles[0] != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Missile at index 0: %s"), *Missiles[0]->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Missiles array is empty or index 0 is nullptr"));
	}

}

void UHeliAttackComp::SetupPlayerInput(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInput(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	// Ű���� ���ε�
	if (EnhancedInputComponent) {

		EnhancedInputComponent->BindAction(IA_Heli_MachineGunShoot, ETriggerEvent::Triggered, this, &UHeliAttackComp::Shoot_MachineGun);
		EnhancedInputComponent->BindAction(IA_Heli_MachineGunShoot, ETriggerEvent::Completed, this, &UHeliAttackComp::Stop_MGEffect);


		EnhancedInputComponent->BindAction(IA_Heli_MissileShoot, ETriggerEvent::Started, this, &UHeliAttackComp::Shoot_Missile);

		EnhancedInputComponent->BindAction(IA_Heli_Aming, ETriggerEvent::Triggered, this, &UHeliAttackComp::Shoot_Aming);

	}

}

void UHeliAttackComp::Shoot_MachineGun(const FInputActionValue& value)
{
	bool bIsValue = value.Get<bool>();

	// �Ѿ��� �����ϴ� ���
	ABullet_Apache* SpawnBullet = GetWorld()->SpawnActor<ABullet_Apache>(BulletFactory_Apache, Apache->MGNozzleComp->GetComponentLocation(), Apache->MGNozzleComp->GetComponentRotation()/*Apache->GetMesh()->GetSocketRotation(FName("gun_tilt_jntSocket"))*/);

	SpawnBullet->SetOwner(Apache);
	SpawnBullet->SaveOwner();

	// �ѿ��� �Ҳ� ����Ʈ ����
	Apache->MGEffectComp->SetActive(true);

	FHitResult HitResult;
	float AttackRange = 50000.f; // �����Ÿ�
	FVector StartLocation = Apache->CameraLocComp->GetComponentLocation()/* + FVector(-500,0,0)*/;// ���� ��ġ ����
	FVector EndLocation = StartLocation + (Apache->CameraLocComp->GetForwardVector() * AttackRange); // ���� ��ġ ����
	ECollisionChannel TraceChannel = ECollisionChannel::ECC_Visibility; // ���� Ʈ���̽��� ä�� ����
	FCollisionQueryParams CollisionParams; // ������ ����
	CollisionParams.AddIgnoredActor(Cast<AActor>(Apache)); // this�� ���� ������ �����͸� ��Ÿ���ϴ�.

	// ���� Ʈ���̽� ����
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

	// �߻� ���� �ʿ�


}

void UHeliAttackComp::Stop_MGEffect(const FInputActionValue& value)
{
	bool bIsValue = value.Get<bool>();

	// �ѿ��� �Ҳ� ����Ʈ ����
	Apache->MGEffectComp->SetActive(false);

}

void UHeliAttackComp::Shoot_Missile(const FInputActionValue& value)
{
	bool bIsValue = value.Get<bool>();

	if (Missiles.Num() == 0) {
		return;
	}

	FHitResult HitResult;
	float AttackRange = 100000.f; // �����Ÿ�
	FVector StartLocation = Apache->CameraLocComp->GetComponentLocation();// ���� ��ġ ����
	FVector EndLocation = StartLocation + (Apache->CameraLocComp->GetForwardVector() * AttackRange); // ���� ��ġ ����
	ECollisionChannel TraceChannel = ECollisionChannel::ECC_Visibility; // ���� Ʈ���̽��� ä�� ����
	FCollisionQueryParams CollisionParams; // ������ ����
	CollisionParams.AddIgnoredActor(Cast<AActor>(Apache)); // this�� ���� ������ �����͸� ��Ÿ���ϴ�.

	AMissile_Apache* CurrentMissile = Missiles[0];
	CurrentMissile->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

	CurrentMissile->NSComp->SetActive(true);

	// ���� Ʈ���̽� ����
	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, TraceChannel, CollisionParams))
	{
		//DrawDebugLine(GetWorld(), StartLocation, HitResult.ImpactPoint, FColor::Green, false, 5.0f, 0, 5.0f);

		// �������� �̵� - HitResult.Location

		CurrentMissile->MissileMove(HitResult.Location);

	}
	else
	{
		//DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Green, false, 5.0f, 0, 5.0f);

		// �������� �̵� - EndLocation
		CurrentMissile->MissileMove(EndLocation);


	}

	if (Missiles.Num() > 0) {
		Missiles.Remove(CurrentMissile);
	}


}

void UHeliAttackComp::Shoot_Aming(const FInputActionValue& value)
{
	FVector2D bIsValue = value.Get<FVector2D >();


}
