// Fill out your copyright notice in the Description page of Project Settings.


#include "../Tank/FixedTank.h"
#include "../Helicopter/HelicopterBase.h"
#include <../../../../../../../Source/Runtime/AIModule/Classes/Perception/PawnSensingComponent.h>
#include "TimerManager.h"
#include "../Projectile/Bullet_Tank.h"


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

	SetupSpawnTimer();


}

void AFixedTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFixedTank::OnSeePawn(APawn* OtherPawn)
{
	
	
	UE_LOG(LogTemp, Warning, TEXT("OtherPawn Name: %s"), *OtherPawn->GetName());

	Player = Cast<AHelicopterBase>(OtherPawn);

	//Super::OnSeePawn(OtherPawn);

	if (Player)
	{
		UE_LOG(LogTemp, Warning, TEXT("pawnsensing"));


		// ���� ��ġ
		FVector StartLoc = GetActorLocation();

		// ��ǥ ��ġ
		FVector TargetLoc = Player->GetActorLocation(); 

		// ������ ��ġ ���
		FVector NewLoc = FMath::Lerp(StartLoc, TargetLoc, Alpha);

		// ���ο� ��ġ�� �̵�
		//SetActorLocation(NewLoc);

		Direction = NewLoc - StartLoc;


	}
	

	//class AActor* aaa = Cast<AActor>(OtherPawn);

	//if (aaa)
	//{

	//	// ���� ��ġ
	//	FVector StartLoc = GetActorLocation();

	//	// ��ǥ ��ġ
	//	FVector TargetLoc = aaa->GetActorLocation();

	//	// ������ ��ġ ���
	//	FVector NewLoc = FMath::Lerp(StartLoc, TargetLoc, Alpha);

	//	// ���ο� ��ġ�� �̵�
	//	//SetActorLocation(NewLoc);

	//	Direction = NewLoc - StartLoc;

	//}

}


void AFixedTank::SpawnActorFunction()
{
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


void AFixedTank::SetupSpawnTimer()
{
	float SpawnInterval = 2.0f;

	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &AFixedTank::SpawnActorFunction, SpawnInterval, true);

}
