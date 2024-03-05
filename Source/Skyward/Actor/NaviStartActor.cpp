// Fill out your copyright notice in the Description page of Project Settings.


#include "../Actor/NaviStartActor.h"
#include "NaviEndActor.h"

ANaviStartActor::ANaviStartActor()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ANaviStartActor::BeginPlay()
{
	Super::BeginPlay();

	if (Apache && NaviEndActor) {
		NaviLine(GetActorLocation(), GetActorLocation() + FVector(0,0,20000), NaviEndActor->GetActorLocation());
	}

}

void ANaviStartActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ANaviStartActor::NaviLine(FVector P1, FVector P2, FVector P3)
{

	FVector M1;
	FVector M2;
	FVector M3; // 표식 위치 

	

	for (float i = 0; i < 1.f; i += 0.01f)
	{
		M1 = FMath::Lerp(P1, P2, i);
		M2 = FMath::Lerp(P2, P3, i);
		M3 = FMath::Lerp(M1, M2, i);

		DrawDebugLine(GetWorld(), M3, M3 + FVector(100), FColor::Green, false, -1, 0, 100);

		SpawnNaviActor = GetWorld()->SpawnActor<AActor>(NaviActorFactory, M3, FRotator(0));


		linePositionActor.Add(SpawnNaviActor);

	}


}

