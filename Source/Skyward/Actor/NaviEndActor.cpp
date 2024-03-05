// Fill out your copyright notice in the Description page of Project Settings.


#include "../Actor/NaviEndActor.h"
#include "../Helicopter/Helicopter_Apache.h"

ANaviEndActor::ANaviEndActor()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ANaviEndActor::BeginPlay()
{
	Super::BeginPlay();

}

void ANaviEndActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ANaviEndActor::LengthFromHeli()
{
	/*
	FHitResult HitResult;
	float AttackRange = 1000.f; // 사정거리
	ECollisionChannel TraceChannel = ECollisionChannel::ECC_Visibility; // 라인 트레이스할 채널 설정
	FCollisionQueryParams CollisionParams; // 무시할 액터

	 //무시할 액터 저장
	CollisionParams.AddIgnoredActor(Cast<AActor>(this)); // this는 현재 액터의 포인터를 나타냅니다.


	 //라인 트레이스 실행
	GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, TraceChannel, CollisionParams);

	 //자신의 위치에서 Apache까지의 경로를 직선으로 표시
	DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Green, false, -1, 0, 2);
	*/



	FVector StartLocation = GetActorLocation();// 시작 위치 설정
	FVector EndLocation = Apache->GetActorLocation(); // 종료 위치 설정
	
	// 헬기 까지의 거리
	float TraceDistance = FVector::Distance(StartLocation, EndLocation);


	if (TraceDistance > 1000) {
		Destroy();
	}

}