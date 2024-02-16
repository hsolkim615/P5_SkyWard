// Fill out your copyright notice in the Description page of Project Settings.


#include "../Tank/TankFSM.h"

#include "TankBase.h"
#include "Kismet/GameplayStatics.h"
#include "Skyward/Helicopter/HelicopterBase.h"

// Sets default values for this component's properties
UTankFSM::UTankFSM()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTankFSM::BeginPlay()
{
	Super::BeginPlay();

	auto actor = UGameplayStatics::GetActorOfClass(GetWorld(), AHelicopterBase::StaticClass());
	Player = Cast<AHelicopterBase>(actor);
	Me = Cast<ATankBase>(GetOwner());
}


// Called every frame
void UTankFSM::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	 switch (mState)
	 {
	 case EEnemyState::Idle:
		 IdleState();
		 break;
	 case EEnemyState::Attack:
	 	AttackState();
	 	break;
	 case EEnemyState::Die: 
		DieState();
	 	break;
	 }
}


void UTankFSM::IdleState()
{
	FVector PlayerLoc = Player->GetActorLocation();
	FVector EnemyLoc = Me->GetActorLocation();
	FVector Dir = PlayerLoc - EnemyLoc;

	if (Dir.Size() < AttackRange)
	{
		mState = EEnemyState::Attack;
	}

}

void UTankFSM::AttackState()
 {
	CurrentTime += GetWorld()->DeltaTimeSeconds;
	if (CurrentTime > AttackTime)
	{
		CurrentTime = 0;
		
	}

	FVector PlayerLoc = Player->GetActorLocation();
	FVector EnemyLoc = Me->GetActorLocation();
	FVector Dir = PlayerLoc - EnemyLoc;

	if (Dir.Size() > AttackRange)
	{
		mState = EEnemyState::Idle;
		
	}

 }


 void UTankFSM::DieState()
 {
	
 }

 void UTankFSM::OnDamageProcess(int param)
 {
	CurrentHp -= param;

	if (CurrentHp == 0)
	{
		mState = EEnemyState::Die;
	}
 }


