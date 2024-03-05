// Fill out your copyright notice in the Description page of Project Settings.


#include "../Buliding/EnemyBuliding.h"
#include "../Component/StateComponent.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Components/StaticMeshComponent.h>
#include "../GameModeBase/SkywardGameModeBase.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h>

// Sets default values
AEnemyBuliding::AEnemyBuliding()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	SetRootComponent(MeshComp);

	StateComponent = CreateDefaultSubobject<UStateComponent>(TEXT("StateComp"));

}

// Called when the game starts or when spawned
void AEnemyBuliding::BeginPlay()
{
	Super::BeginPlay();
	
	// 게임모드 베이스
	SkywardGM = Cast<ASkywardGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

}

// Called every frame
void AEnemyBuliding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemyBuliding::Damaged()
{
}

void AEnemyBuliding::Die()
{
	if (SkywardGM)
	{
		SkywardGM->DestroyEnemyBuliding++;
	}

	Destroy();
}

