// Fill out your copyright notice in the Description page of Project Settings.


#include "../Tank/FixedTank.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Components/AudioComponent.h>
#include "../Projectile/Bullet_Tank.h"
#include <../../../../../../../Plugins/FX/Niagara/Source/Niagara/Public/NiagaraFunctionLibrary.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Engine/TimerHandle.h>
#include <../../../../../../../Plugins/FX/Niagara/Source/Niagara/Classes/NiagaraSystem.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Sound/SoundWave.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Engine/SkeletalMesh.h>

AFixedTank::AFixedTank()
{
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<USkeletalMesh>TempMesh(TEXT("C:/Users/ASUS/Desktop/Git_Final/SkyWard/Content/Resource/KJY/Damaged/FixedDamaged.uasset"));
	
	if (TempMesh.Succeeded())
	{
		//GetMesh()->SkeletalMesh
	}
	
}

void AFixedTank::BeginPlay()
{
	Super::BeginPlay();


}

void AFixedTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFixedTank::SpawnBullet()
{
	UE_LOG(LogTemp, Warning, TEXT("spawn"));

	// GetWorld() 함수를 사용하여 현재 월드에 접근
	UWorld* World = GetWorld();
	if (World)
	{
		UAudioComponent* AudioComponent = UGameplayStatics::SpawnSound2D(World, FireSound, 1.0f, 1.0f, 0.0f, nullptr, false, true);


		FTransform SocketTransform = GetMesh()->GetSocketTransform(FName("gun_jntSocket_Shot"));
		FVector SpawnLocation = SocketTransform.GetLocation();
		FRotator SpawnRotation = SocketTransform.GetRotation().Rotator();



		// 액터 스폰
		ABullet_Tank* SpawnedActor = World->SpawnActor<ABullet_Tank>(BulletClass, SpawnLocation, SpawnRotation);



		//UNiagaraSystem* NiagaraSystem = LoadObject<UNiagaraSystem>(nullptr, TEXT("C:/Users/ASUS/Desktop/Git_Final/SkyWard/Content/Tank_M109_Project/West_SPG_M109/FX/NS_East_Tank_T72B.uasset"));

		if (FireEffect)
		{
			//UNiagaraComponent* NiagaraComponent = 

			UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), FireEffect, SpawnLocation, SpawnRotation);
		}

		bTimer = false;
	}
}

void AFixedTank::Damaged()
{
	//NewMesh = nullptr; // 초기화된 메쉬 포인터
	//
	//// NewMesh에 특정 스태틱 메쉬를 할당
	//NewMesh = Cast<USkeletalMesh>(StaticLoadObject(USkeletalMesh::StaticClass(), nullptr, TEXT("C:/Users/ASUS/Desktop/Git_Final/SkyWard/Content/Resource/KJY/Damaged/FixedDamaged.uasset")));
	//GetMesh()->SetSkeletalMesh(NewMesh);
}

void AFixedTank::Die()
{
	Destroy();

}

//void AFixedTank::SetupTimer()
//{
//	UE_LOG(LogTemp, Warning, TEXT("timer"));
//
//	if (GetWorld()->GetTimerManager().IsTimerActive(TimerHandle)) {
//		return;
//	}
//
//	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AFixedTank::SpawnBullet, Interval, false);
//
//}

//void AFixedTank::ResetDetection()
//{
//	bTimer = true;
//}

