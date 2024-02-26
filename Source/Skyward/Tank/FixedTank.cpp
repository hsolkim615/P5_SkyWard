// Fill out your copyright notice in the Description page of Project Settings.


#include "../Tank/FixedTank.h"
#include "../Helicopter/HelicopterBase.h"
#include <../../../../../../../Source/Runtime/AIModule/Classes/Perception/PawnSensingComponent.h>
#include "TimerManager.h"
#include "../Projectile/Bullet_Tank.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h>


AFixedTank::AFixedTank()
{
	PrimaryActorTick.bCanEverTick = true;

	// boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	// SetRootComponent(boxComp);
	//
	// meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	// meshComp->SetupAttachment(boxComp);

	//FSM = CreateDefaultSubobject<UTankFSM>(TEXT("FSM"));

	pawnSensing = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("pawnSensing"));
	// OnSeePawn �̺�Ʈ�� ���� �ڵ鷯�� ���ε��մϴ�.
	

}

void AFixedTank::BeginPlay()
{
	Super::BeginPlay();

	if (pawnSensing)
	{

		pawnSensing->OnSeePawn.AddDynamic(this, &AFixedTank::OnSeePawn);
	}
	//Player = Cast<AHelicopterBase>(GetOwner());

	SetupTimer();


}

void AFixedTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFixedTank::OnSeePawn(APawn* OtherPawn)
{
	if (bCanDetectPlayer && OtherPawn && OtherPawn->IsA<AHelicopterBase>())
	{
		Player = Cast<AHelicopterBase>(OtherPawn);

		AimingPlayer();

		//bCanDetectPlayer = false;
		//SetupTimer();

		UE_LOG(LogTemp, Warning, TEXT("sssssss"));

	
		/*CurrentTime += GetWorld()->DeltaTimeSeconds;
		if (CurrentTime > AimingTime)
		{
			UE_LOG(LogTemp, Warning, TEXT("aimingTime"));

			CurrentTime = 0;
			AimingPlayer();
		}*/
	}

	//UE_LOG(LogTemp, Warning, TEXT("OtherPawn Name: %s"), *OtherPawn->GetName());

	//Player = Cast<AHelicopterBase>(OtherPawn);

	////Super::OnSeePawn(OtherPawn);

	//if (Player)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("Player"));

	//	SetupTimer();

	//}
	
	

}


void AFixedTank::SpawnBullet()
{
	UE_LOG(LogTemp, Warning, TEXT("spawn"));

	// GetWorld() �Լ��� ����Ͽ� ���� ���忡 ����
	UWorld* World = GetWorld();
	if (World)
	{

		FTransform SocketTransform = GetMesh()->GetSocketTransform(FName("gun_jntSocket"));
		FVector SpawnLocation = SocketTransform.GetLocation();
		FRotator SpawnRotation = SocketTransform.GetRotation().Rotator();

		// ������ ������ Ŭ������ �����մϴ�.
		//ActorClass = ABullet_Tank::StaticClass();

		// ���� ����
		ABullet_Tank* SpawnedActor = World->SpawnActor<ABullet_Tank>(ActorClass, SpawnLocation, SpawnRotation);

		//if (SpawnedActor)
		//{
		//	// ���Ͱ� ���������� �����Ǿ��� �� �߰����� ������ ������ �� �ֽ��ϴ�.
		//}


	}
}


void AFixedTank::SetupTimer()
{
	UE_LOG(LogTemp, Warning, TEXT("timer"));

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AFixedTank::SpawnBullet, Interval, true);



}

void AFixedTank::AimingPlayer()
{
	UE_LOG(LogTemp, Warning, TEXT("aiming"));

	// ���� ��ġ
	FVector StartLoc = GetActorLocation();
	FTransform SocketTransform = GetMesh()->GetSocketTransform(FName("gun_jntSocket"));
	FVector SpawnLocation = SocketTransform.GetLocation();

	// ��ǥ ��ġ
	if (!Player) {
		return;
	}
	FVector TargetLoc = Player->GetActorLocation();

	// ������ ��ġ ���
	//FVector NewLoc = FMath::Lerp(StartLoc, TargetLoc, Alpha);

	float DeltaTime = GetWorld()->GetDeltaSeconds();


	FVector NewLoc = FMath::VInterpTo(StartLoc, TargetLoc, DeltaTime, InterpSpeed);


	// ���ο� ��ġ�� �̵�
	//SetActorLocation(NewLoc);

	Direction = (NewLoc - StartLoc).GetSafeNormal();

	//SpawnBullet();
	//SetupTimer();

	FHitResult HitResult;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this); // �ڱ� �ڽ��� ����

	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLoc, TargetLoc, ECC_Visibility, CollisionParams))
	{
		// ��ǥ���� �浹�� ���
		Player = Cast<AHelicopterBase>(GetOwner());
		if (Player)
		{
			UE_LOG(LogTemp, Warning, TEXT("Player Detected! Fire Bullet!"));

			//SpawnBullet();
			
		}
	}


	//// ���� �׸��� ���� ����� ���� �Լ� ȣ��
	//DrawDebugLine(
	//	GetWorld(),    // UWorld ��ü
	//	StartLoc,         // ������
	//	TargetLoc,           // ����
	//	FColor::Red, // ���� ����
	//	true,         // ���� ���������� ���� (false�� ����)
	//	5.0f,         // ���� ���� �ð� (-1.0f�� �����ϸ� �� ������ ���� ���ӵ�)
	//	10,             // �β� (�⺻�� 0)
	//	1.0f          // Depth priority (�⺻�� 1.0f)
	//);
}

void AFixedTank::ResetDetection()
{
	bCanDetectPlayer = true;
}

