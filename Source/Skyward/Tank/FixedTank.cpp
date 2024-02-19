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
	// OnSeePawn 이벤트에 대한 핸들러를 바인딩합니다.
	

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


		// 현재 위치
		FVector StartLoc = GetActorLocation();

		// 목표 위치
		FVector TargetLoc = Player->GetActorLocation(); 

		// 보간된 위치 계산
		FVector NewLoc = FMath::Lerp(StartLoc, TargetLoc, Alpha);

		// 새로운 위치로 이동
		//SetActorLocation(NewLoc);

		Direction = NewLoc - StartLoc;


	}
	

	//class AActor* aaa = Cast<AActor>(OtherPawn);

	//if (aaa)
	//{

	//	// 현재 위치
	//	FVector StartLoc = GetActorLocation();

	//	// 목표 위치
	//	FVector TargetLoc = aaa->GetActorLocation();

	//	// 보간된 위치 계산
	//	FVector NewLoc = FMath::Lerp(StartLoc, TargetLoc, Alpha);

	//	// 새로운 위치로 이동
	//	//SetActorLocation(NewLoc);

	//	Direction = NewLoc - StartLoc;

	//}

}


void AFixedTank::SpawnActorFunction()
{
	// GetWorld() 함수를 사용하여 현재 월드에 접근합니다.
	UWorld* World = GetWorld();
	if (World)
	{

		FTransform SocketTransform = GetMesh()->GetSocketTransform(FName("gun_jntSocket"));
		FVector SpawnLocation = SocketTransform.GetLocation();
		FRotator SpawnRotation = SocketTransform.GetRotation().Rotator();

		// 스폰할 액터의 클래스를 지정합니다.
		//ActorClass = ABullet_Tank::StaticClass();

		// 액터를 스폰합니다.
		ABullet_Tank* SpawnedActor = World->SpawnActor<ABullet_Tank>(ActorClass, SpawnLocation, SpawnRotation);

		//if (SpawnedActor)
		//{
		//	// 액터가 성공적으로 스폰되었을 때 추가적인 로직을 수행할 수 있습니다.
		//}


	}
}

// 액터를 주기적으로 스폰하기 위한 타이머를 설정하는 함수를 정의합니다.
void AFixedTank::SetupSpawnTimer()
{
	// 타이머 주기를 설정합니다. 여기서는 2초로 설정합니다.
	float SpawnInterval = 2.0f;

	// 타이머를 설정합니다.
	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &AFixedTank::SpawnActorFunction, SpawnInterval, true);

}
