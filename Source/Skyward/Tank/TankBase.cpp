// Fill out your copyright notice in the Description page of Project Settings.


#include "../Tank/TankBase.h"
#include "../Helicopter/HelicopterBase.h"
#include <../../../../../../../Source/Runtime/AIModule/Classes/Perception/PawnSensingComponent.h>
#include <../../../../../../../Source/Runtime/Engine/Public/TimerManager.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Engine/TimerHandle.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/GameFramework/Actor.h>
#include "../Projectile/Bullet_Tank.h"
#include <../../../../../../../Plugins/FX/Niagara/Source/Niagara/Public/NiagaraComponent.h>
#include <../../../../../../../Plugins/FX/Niagara/Source/Niagara/Classes/NiagaraSystem.h>
#include <../../../../../../../Plugins/FX/Niagara/Source/Niagara/Public/NiagaraFunctionLibrary.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Components/AudioComponent.h>
#include "../Component/StateComponent.h"
#include "../GameModeBase/SkywardGameModeBase.h"

ATankBase::ATankBase()
{
	PrimaryActorTick.bCanEverTick = true;

	pawnSensing = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("pawnSensing"));

	StateComponent = CreateDefaultSubobject<UStateComponent>(TEXT("StateComponent"));

	//NiagaraComp = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComp"));


}

void ATankBase::BeginPlay()
{
	Super::BeginPlay();


	// ���Ӹ�� ���̽�
	SkywardGM = Cast<ASkywardGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	if (pawnSensing)
	{
		pawnSensing->OnSeePawn.AddDynamic(this, &ATankBase::OnSeePawn);
	}

	//NiagaraComp->Activate(false);
}

void ATankBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bTimer) {
		SetupTimer();
	}
}

void ATankBase::OnSeePawn(APawn* OtherPawn)
{
	//Super::OnSeePawn(OtherPawn);

	UE_LOG(LogTemp, Warning, TEXT("onseepawn"));

	if (OtherPawn && OtherPawn->IsA<AHelicopterBase>())
	{
		UE_LOG(LogTemp, Warning, TEXT("player"));

		Player = Cast<AHelicopterBase>(OtherPawn);

		AimingPlayer();

		bTimer = true;

	}
}


void ATankBase::AimingPlayer()
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
	//UE_LOG(LogTemp, Warning, TEXT("%f"),DeltaTime);


	FVector NewLoc = FMath::VInterpTo(StartLoc, TargetLoc, DeltaTime, InterpSpeed);


	// ���ο� ��ġ�� �̵�
	//SetActorLocation(NewLoc);

	Direction = (NewLoc - StartLoc).GetSafeNormal();

	//SpawnBullet();
	//SetupTimer();

	FHitResult HitResult;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this); // �ڱ� �ڽ��� ����

	//if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLoc, TargetLoc, ECC_Visibility, CollisionParams))
	//{
	//	// ��ǥ���� �浹�� ���
	//	Player = Cast<AHelicopterBase>(GetOwner());
	//	if (Player)
	//	{
	//		//UE_LOG(LogTemp, Warning, TEXT("Player Detected! Fire Bullet!"));

	//		//SpawnBullet();

	//	}
	//}

	bTimer = true;


	//// ���� �׸��� ���� ����� ���� �Լ� ȣ��
	//DrawDebugLine(
	//	GetWorld(),    // UWorld ��ü
	//	StartLoc,         // ������
	//	TargetLoc,           // ����
	//	FColor::Red, // ���� ����
	//	true,         // ���� ���������� ���� (false�� ����)
	//	10.0f,         // ���� ���� �ð� (-1.0f�� �����ϸ� �� ������ ���� ���ӵ�)
	//	10,             // �β� (�⺻�� 0)
	//	1.0f          // Depth priority (�⺻�� 1.0f)
	//);
}


void ATankBase::SpawnBullet()
{
	//UE_LOG(LogTemp, Warning, TEXT("spawn"));

	//// GetWorld() �Լ��� ����Ͽ� ���� ���忡 ����
	//UWorld* World = GetWorld();
	//if (World)
	//{
	//	UAudioComponent* AudioComponent = UGameplayStatics::SpawnSound2D(World, FireSound, 1.0f, 1.0f, 0.0f, nullptr, false, true);


	//	FTransform SocketTransform = GetMesh()->GetSocketTransform(FName("gun_jntSocket_Shot"));
	//	FVector SpawnLocation = SocketTransform.GetLocation();
	//	FRotator SpawnRotation = SocketTransform.GetRotation().Rotator();



	//	// ���� ����
	//	ABullet_Tank* SpawnedActor = World->SpawnActor<ABullet_Tank>(ActorClass, SpawnLocation, SpawnRotation);

	//	//UNiagaraSystem* NiagaraSystem = LoadObject<UNiagaraSystem>(nullptr, TEXT("C:/Users/ASUS/Desktop/Git_Final/SkyWard/Content/Tank_M109_Project/West_SPG_M109/FX/NS_East_Tank_T72B.uasset"));

	//	if (Flame_Fire)
	//	{
	//		//UNiagaraComponent* NiagaraComponent = 

	//		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Flame_Fire, SpawnLocation, SpawnRotation);
	//	}

	//	bTimer = false;
	//}
}


void ATankBase::SetupTimer()
{
	UE_LOG(LogTemp, Warning, TEXT("timer"));

	if (GetWorld()->GetTimerManager().IsTimerActive(TimerHandle)) {
		return;
	}

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ATankBase::SpawnBullet, Interval, false);

}

void ATankBase::Damaged()
{
	//NiagaraComp->Activate(true);
}

void ATankBase::Die()
{
	
}
