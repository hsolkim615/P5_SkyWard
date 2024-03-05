// Fill out your copyright notice in the Description page of Project Settings.


#include "../Projectile/Bullet_Apache.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/GameFramework/ProjectileMovementComponent.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Components/SphereComponent.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/KismetMathLibrary.h>
#include "../Tank/TankBase.h"
#include "../Helicopter/Helicopter_Apache.h"
#include <../../../../../../../Plugins/FX/Niagara/Source/Niagara/Public/NiagaraFunctionLibrary.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Sound/SoundBase.h>
#include "../Component/StateComponent.h"
#include "../Buliding/Bunker.h"
#include "../Buliding/EnemyBuliding.h"

ABullet_Apache::ABullet_Apache()
{
	PrimaryActorTick.bCanEverTick = true;

	// �Ѿ� �ݸ���
	HitCollision = CreateDefaultSubobject<USphereComponent>(TEXT("HitCollision"));
	SetRootComponent(HitCollision);

	// �Ѿ� ����
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(RootComponent);
	MeshComp->SetRelativeRotation(FRotator(90, 0, 0));

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
	FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, 100000.f);
	SetActorLocation(NewLocation);

}

void ABullet_Apache::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), NSBullet, GetActorLocation(), FRotator(0), FVector(0.01f));


	if (OtherActor->GetComponentByClass<UStateComponent>()) {


		// ***** �������� �ִ� ������� ���� �ʿ� / ��ũ�� ���� �ִ� StateCompoenet�� �Լ��� ȣ���� ��
		//UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), NSBullet, TargetLocation, FRotator(0), FVector(3));


		if (OtherActor->IsA<ATankBase>()) {

			// StateComponent�� �̿��� ü���� ���ҽ�Ű�� ������� ����


			Cast<ATankBase>(OtherActor)->StateComponent->TakeDamage(20);

		}
		else if (OtherActor->IsA<ABunker>()) {

			Cast<ABunker>(OtherActor)->StateComponent->TakeDamage(20);


		}
		else if (OtherActor->IsA<AEnemyBuliding>()) {

			Cast<AEnemyBuliding>(OtherActor)->StateComponent->TakeDamage(20);


		}

	}

}

void ABullet_Apache::BulletMove(FVector TargetLoc)
{
	// �̵� ���� �ʿ�

	TargetLocation = TargetLoc;

}

void ABullet_Apache::SaveOwner()
{
	Apache = Cast<AHelicopter_Apache>(GetOwner());

}

void ABullet_Apache::setAttackDamage(float NewAttackDamage)
{

}
