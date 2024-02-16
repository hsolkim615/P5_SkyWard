// Fill out your copyright notice in the Description page of Project Settings.


#include "../Tank/FixedTank.h"
#include "../Helicopter/HelicopterBase.h"
#include <../../../../../../../Source/Runtime/AIModule/Classes/Perception/PawnSensingComponent.h>


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

