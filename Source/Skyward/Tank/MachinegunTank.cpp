// Fill out your copyright notice in the Description page of Project Settings.


#include "../Tank/MachinegunTank.h"
#include <../../../../../../../Plugins/FX/Niagara/Source/Niagara/Public/NiagaraFunctionLibrary.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Engine/TimerHandle.h>
#include "../Projectile/Bullet_Tank.h"

AMachinegunTank::AMachinegunTank()
{
	PrimaryActorTick.bCanEverTick = true;



}

void AMachinegunTank::BeginPlay()
{
	Super::BeginPlay();

}

void AMachinegunTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMachinegunTank::SpawnBullet()
{
	UE_LOG(LogTemp, Warning, TEXT("spawn"));

	// GetWorld() �Լ��� ����Ͽ� ���� ���忡 ����
	UWorld* World = GetWorld();
	if (World)
	{

		FTransform SocketTransform = GetMesh()->GetSocketTransform(FName("gun_jntSocket_Shot"));
		FVector SpawnLocation = SocketTransform.GetLocation();
		FRotator SpawnRotation = SocketTransform.GetRotation().Rotator();

		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AMachinegunTank::Spawn, Machine_Interval, true);

		//UNiagaraSystem* NiagaraSystem = LoadObject<UNiagaraSystem>(nullptr, TEXT("C:/Users/ASUS/Desktop/Git_Final/SkyWard/Content/Tank_M109_Project/West_SPG_M109/FX/NS_East_Tank_T72B.uasset"));

		if (FireEffect)
		{
			//UNiagaraComponent* NiagaraComponent = 

			UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), FireEffect, SpawnLocation, SpawnRotation);
		}

	//	bTimer = false;	
	}
}

void AMachinegunTank::Spawn()
{
	UWorld* World = GetWorld();
	if (World)
	{
		UAudioComponent* AudioComponent = UGameplayStatics::SpawnSound2D(World, FireSound, 1.0f, 1.0f, 0.0f, nullptr, false, true);


		FTransform SocketTransform = GetMesh()->GetSocketTransform(FName("gun_jntSocket_Shot"));
		FVector SpawnLocation = SocketTransform.GetLocation();
		FRotator SpawnRotation = SocketTransform.GetRotation().Rotator();

		// ���� ����
		ABullet_Tank* SpawnedActor = World->SpawnActor<ABullet_Tank>(BulletClass, SpawnLocation, SpawnRotation);
	
		NumBulletsShot++;

		// �߻� Ƚ���� ���ѿ� �����ϸ� Ÿ�̸� ����
		if (NumBulletsShot >= NumBulletsToShoot)
		{
			//GetWorldTimerManager().ClearTimer(TimerHandle);
			GetWorldTimerManager().PauseTimer(TimerHandle);
			NumBulletsShot = 0; // �߻� Ƚ�� �ʱ�ȭ

			bTimer = false;
		}
	}
}

void AMachinegunTank::Damaged()
{

}

void AMachinegunTank::Die()
{

}

//void AMachinegunTank::SetupTimer()
//{
//	UE_LOG(LogTemp, Warning, TEXT("timer"));
//
//	if (GetWorld()->GetTimerManager().IsTimerActive(TimerHandle)) {
//		return;
//	}
//
//	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AMachinegunTank::SpawnBullet, Interval, false);
//
//}


