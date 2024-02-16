// Fill out your copyright notice in the Description page of Project Settings.


#include "../Tank/TankBase.h"

#include "TankFSM.h"
#include "Components/BoxComponent.h"

ATankBase::ATankBase()
{
	PrimaryActorTick.bCanEverTick = true;
 
	// boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	// SetRootComponent(boxComp);
	//
	// meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	// meshComp->SetupAttachment(boxComp);

	//FSM = CreateDefaultSubobject<UTankFSM>(TEXT("FSM"));
}

void ATankBase::BeginPlay()
{
	Super::BeginPlay();

	//CurrentHp = MaxHp;

}

void ATankBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/*FVector PlayerLoc = Player->GetActorLocation();
	FVector EnemyLoc = Me->GetActorLocation();
	FVector Dir = PlayerLoc - EnemyLoc;
	if (Dir < AttackRange)
	{
		Attack();
	}*/


}

//void ATankBase::Attack()
//{
//	CurrentTime += GetWorld()->DeltaTimeSeconds;
//	// 총알 발사
//	if (CurrentTime > AttackTime)
//	{
//		CurrentTime = 0;
//
//
//	}
//	
//}
//
//// 피격 시 플레이어 쪽에서 호출
//void ATankBase::Damage(Param)
//{
//	CurrentHp -= Param;
//	UE_LOG(LogTemp, Warning, TEXT("Damage"));
//
//	if (CurrentHp == 0)
//	{
//		Die();
//	}
//}
//
//void ATankBase::Die()
//{
//	Destroy();
//}
//
//void ATankBase::DrawTrajectory()
//{
//	GetMesh()->transform
//}

