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
	float AttackRange = 1000.f; // �����Ÿ�
	ECollisionChannel TraceChannel = ECollisionChannel::ECC_Visibility; // ���� Ʈ���̽��� ä�� ����
	FCollisionQueryParams CollisionParams; // ������ ����

	 //������ ���� ����
	CollisionParams.AddIgnoredActor(Cast<AActor>(this)); // this�� ���� ������ �����͸� ��Ÿ���ϴ�.


	 //���� Ʈ���̽� ����
	GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, TraceChannel, CollisionParams);

	 //�ڽ��� ��ġ���� Apache������ ��θ� �������� ǥ��
	DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Green, false, -1, 0, 2);
	*/



	FVector StartLocation = GetActorLocation();// ���� ��ġ ����
	FVector EndLocation = Apache->GetActorLocation(); // ���� ��ġ ����
	
	// ��� ������ �Ÿ�
	float TraceDistance = FVector::Distance(StartLocation, EndLocation);


	if (TraceDistance > 1000) {
		Destroy();
	}

}