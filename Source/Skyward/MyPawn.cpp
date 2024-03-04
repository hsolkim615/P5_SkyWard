// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"
#include "Actor/Destination.h"
#include <../../../../../../../Source/Runtime/AIModule/Classes/AIController.h>
#include <../../../../../../../Source/Runtime/NavigationSystem/Public/NavigationSystem.h>

// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
	
	ai = Cast<AAIController>(GetController());

	
}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
	YourNavigationFunction();


}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMyPawn::YourNavigationFunction()
{
	// NavMesh�� ����� �� UNavigationSystem�� ����ϴ�.
	UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
	if (NavSys)
	{
		// NavMesh �����Ϳ� �����Ͽ� �ʿ��� ������ ����ϴ�.
		// ���� ���, GetNavMeshBounds() �Լ��� ����Ͽ� NavMesh�� ��踦 ���� �� �ֽ��ϴ�.
		//FBox NavMeshBounds = NavSys->GetNavMeshBounds();

		if (ai)
		{

			if (!Dest)
			{
				UE_LOG(LogTemp, Error, TEXT("Dest variable is NULL"));
				return;
			}

			FVector dest = Dest->GetActorLocation();
			ai->MoveToLocation(dest);
		}

	}
}