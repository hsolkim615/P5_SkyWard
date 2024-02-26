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

	// GetWorld() 함수를 사용하여 현재 월드에 접근
	UWorld* World = GetWorld();
	if (World)
	{

		FTransform SocketTransform = GetMesh()->GetSocketTransform(FName("gun_jntSocket"));
		FVector SpawnLocation = SocketTransform.GetLocation();
		FRotator SpawnRotation = SocketTransform.GetRotation().Rotator();

		// 스폰할 액터의 클래스를 지정합니다.
		//ActorClass = ABullet_Tank::StaticClass();

		// 액터 스폰
		ABullet_Tank* SpawnedActor = World->SpawnActor<ABullet_Tank>(ActorClass, SpawnLocation, SpawnRotation);

		//if (SpawnedActor)
		//{
		//	// 액터가 성공적으로 스폰되었을 때 추가적인 로직을 수행할 수 있습니다.
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

	// 현재 위치
	FVector StartLoc = GetActorLocation();
	FTransform SocketTransform = GetMesh()->GetSocketTransform(FName("gun_jntSocket"));
	FVector SpawnLocation = SocketTransform.GetLocation();

	// 목표 위치
	if (!Player) {
		return;
	}
	FVector TargetLoc = Player->GetActorLocation();

	// 보간된 위치 계산
	//FVector NewLoc = FMath::Lerp(StartLoc, TargetLoc, Alpha);

	float DeltaTime = GetWorld()->GetDeltaSeconds();


	FVector NewLoc = FMath::VInterpTo(StartLoc, TargetLoc, DeltaTime, InterpSpeed);


	// 새로운 위치로 이동
	//SetActorLocation(NewLoc);

	Direction = (NewLoc - StartLoc).GetSafeNormal();

	//SpawnBullet();
	//SetupTimer();

	FHitResult HitResult;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this); // 자기 자신은 무시

	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLoc, TargetLoc, ECC_Visibility, CollisionParams))
	{
		// 목표물과 충돌한 경우
		Player = Cast<AHelicopterBase>(GetOwner());
		if (Player)
		{
			UE_LOG(LogTemp, Warning, TEXT("Player Detected! Fire Bullet!"));

			//SpawnBullet();
			
		}
	}


	//// 선을 그리기 위한 디버깅 목적 함수 호출
	//DrawDebugLine(
	//	GetWorld(),    // UWorld 객체
	//	StartLoc,         // 시작점
	//	TargetLoc,           // 끝점
	//	FColor::Red, // 선의 색상
	//	true,         // 선이 불투명한지 여부 (false면 투명)
	//	5.0f,         // 선의 지속 시간 (-1.0f로 설정하면 한 프레임 동안 지속됨)
	//	10,             // 두께 (기본값 0)
	//	1.0f          // Depth priority (기본값 1.0f)
	//);
}

void AFixedTank::ResetDetection()
{
	bCanDetectPlayer = true;
}

