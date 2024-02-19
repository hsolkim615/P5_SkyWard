// Fill out your copyright notice in the Description page of Project Settings.


#include "../Projectile/Bullet_Apache.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/GameFramework/ProjectileMovementComponent.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Components/SphereComponent.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/KismetMathLibrary.h>

ABullet_Apache::ABullet_Apache()
{
	PrimaryActorTick.bCanEverTick = true;

	// �Ѿ� �ݸ���
	HitCollision = CreateDefaultSubobject<USphereComponent>(TEXT("HitCollision"));
	SetRootComponent(HitCollision);
	HitCollision->SetRelativeScale3D(FVector(0.05f));

	// �Ѿ� ����
	MeshComp->SetupAttachment(RootComponent);
	MeshComp->SetRelativeRotation(FRotator(90, 0, 0));
	MeshComp->SetRelativeScale3D(FVector(0.5f, 0.5, 1.f));

	// �߻�ü ������Ʈ
	//MoveComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MoveComp"));

}

void ABullet_Apache::BeginPlay()
{
	Super::BeginPlay();

	/*
	FTimerHandle TimerHandle;
	float DelayInSeconds = 10.0f; // �ı��� �ð�(��)�� ����

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this]()
		{
			// Ÿ�̸� �ݹ� �Լ� ������ ���͸� �ı�
			Destroy();
		}, DelayInSeconds, false);
	*/

	float DelayInSeconds = 10.0f; // �ı��� �ð�(��)�� ����

	SetLifeSpan(DelayInSeconds);

}

void ABullet_Apache::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);



	// ��ǥ ��ġ�� �ε巴�� �̵�
	FVector CurrentLocation = GetActorLocation();
	FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, 10000.f);
	SetActorLocation(NewLocation);



}

void ABullet_Apache::BulletMove(FVector TargetLoc)
{
	// �̵� ���� �ʿ�

	/*
	FVector TargetLocation = GetActorLocation();
	FRotator TargetRotation = HitCollision->GetComponentRotation();
	float MoveTime = UKismetMathLibrary::Vector_Distance(TargetLocation, TargetLoc) / 500.f; // �̵��� �ɸ��� �ð� ���

	// MoveComponentTo �Լ��� ȣ���Ͽ� HitCollision�� TargetLocation���� �̵���ŵ�ϴ�.
	UKismetSystemLibrary::MoveComponentTo(HitCollision, TargetLocation, HitCollision->GetComponentRotation(), false, false, MoveTime, false, EMoveComponentAction::Type::Move, FLatentActionInfo());
	*/

	TargetLocation = TargetLoc;


}
