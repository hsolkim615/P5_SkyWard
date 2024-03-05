// Fill out your copyright notice in the Description page of Project Settings.


#include "../Tank/MovableTank.h"
#include "../Wheel/Wheel_MovableTank.h"
#include "../Actor/Path.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Components/SplineComponent.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/KismetMathLibrary.h>
#include <ChaosWheeledVehicleMovementComponent.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h>
#include "../Actor/Destination.h"
#include <../../../../../../../Source/Runtime/AIModule/Classes/AIController.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Components/SplineComponent.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Components/SceneComponent.h>
#include <../../../../../../../Plugins/FX/Niagara/Source/Niagara/Public/NiagaraFunctionLibrary.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Components/AudioComponent.h>
#include "../Projectile/Bullet_Tank.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Engine/SkeletalMesh.h>
#include "../GameModeBase/SkywardGameModeBase.h"


AMovableTank::AMovableTank()
{


//	ChaosWheeledVehicleMovementComponent = CreateDefaultSubobject<UChaosWheeledVehicleMovementComponent>(TEXT("ChaosWheeledVehicleMovementComponent"));
	
	//LP = CreateDefaultSubobject<USceneComponent>(TEXT("LP"));
	////LP->SetRelativeLocation(FVector(340.0f, -140.0f, 0.0f));
	//RP = CreateDefaultSubobject<USceneComponent>(TEXT("RP"));
	////RP->SetRelativeLocation(FVector(340.0f, 140.0f, 0.0f));

}

// Called when the game starts or when spawned
void AMovableTank::BeginPlay()
{
	Super::BeginPlay();

	//FoundActor = Cast<APath>(UGameplayStatics::GetActorOfClass(GetWorld(), APath::StaticClass()));
	//if (FoundActor)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("FoundActor: %s"), *FoundActor->GetName());
	//}
	//else
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("FoundActor is NULL"));
	//}*/

	/*ai = Cast<AAIController>(GetController());

	if (ai)
	{	

		if (!Dest)
		{
			UE_LOG(LogTemp, Error, TEXT("Dest variable is NULL"));
			return;
		}

		FVector dest = Dest->GetActorLocation();
		ai->MoveToLocation(dest);
	
	}*/

}

// Called every frame
void AMovableTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//FindPath(FoundActor);

	/*GetVehicleMovement()->SetSteeringInput(0.1f);

	GetVehicleMovement()->SetThrottleInput(0.2f);*/

	//if (Road && Spline)
	//{
	//	//SplineDist = Road->SplineComp;

	//	FVector TargetPoint = Spline->GetLocationAtDistanceAlongSpline(SplineDist, ESplineCoordinateSpace::World);


	//	float Distance = UKismetMathLibrary::Vector_Distance(TargetPoint, GetActorLocation());

	//


	//if (CheckGap > Distance)
	//{
	//	SplineDist += CheckGap;
	//}
	//UE_LOG(LogTemp, Warning, TEXT("%f"), SplineDist);


	////float LPDist = UKismetMathLibrary::Vector_Distance(TargetPoint, LP->GetComponentLocation());
	////float RPDist = UKismetMathLibrary::Vector_Distance(TargetPoint, RP->GetComponentLocation());

	////float LPDist = LPDistVector.Size(); 
	////float RPDist = RPDistVector.Size(); 
	//bool Condition ;

	///*if (LPDist > RPDist) {
	//	Condition = true;
	//}
	//else {
	//	Condition = false;

	//}*/


	//float Steering = UKismetMathLibrary::SelectFloat(0.6f, -0.6f, Condition);

	//


	//}



}

void AMovableTank::SpawnBullet()
{
	UE_LOG(LogTemp, Warning, TEXT("spawn"));

	// GetWorld() �Լ��� ����Ͽ� ���� ���忡 ����
	UWorld* World = GetWorld();
	if (World)
	{
		UAudioComponent* AudioComponent = UGameplayStatics::SpawnSound2D(World, FireSound, 1.0f, 1.0f, 0.0f, nullptr, false, true);


		FTransform SocketTransform = GetMesh()->GetSocketTransform(FName("gun_jntSocket_Shot"));
		FVector SpawnLocation = SocketTransform.GetLocation();
		FRotator SpawnRotation = SocketTransform.GetRotation().Rotator();



		// ���� ����
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

void AMovableTank::Damaged()
{
	NewMesh = nullptr; // �ʱ�ȭ�� �޽� ������

	// NewMesh�� Ư�� ����ƽ �޽��� �Ҵ�
	NewMesh = Cast<USkeletalMesh>(StaticLoadObject(USkeletalMesh::StaticClass(), nullptr, TEXT("C:/Users/ASUS/Desktop/Git_Final/SkyWard/Content/Resource/KJY/Damaged/MovableDamaged.uasset")));
	GetMesh()->SetSkeletalMesh(NewMesh);
}

void AMovableTank::Die()
{
	if (SkywardGM)
	{
		SkywardGM->DestroyMoveTank++;
	}

	Destroy();
}

//void AMovableTank::SetupTimer()
//{
//	UE_LOG(LogTemp, Warning, TEXT("timer"));
//
//	if (GetWorld()->GetTimerManager().IsTimerActive(TimerHandle)) {
//		return;
//	}
//
//	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AMovableTank::SpawnBullet, Interval, false);
//
//}

//
//void AMovableTank::MoveTank()
//{
//	
//	if (Target && ai)
//	{
//		FVector Destination = Target->GetActorLocation();
//
//		if (Player)
//		{
//			// �̵� ����
//			ai->StopMovement();
//
//			// �÷��̾ ����
//			AimingPlayer();
//		}
//		else
//		{
//			// �÷��̾ �������� �ʾ��� ��� ��� �̵�
//			ai->MoveToLocation(Destination);
//		}
//	}
//
//}


//
//void AMovableTank::FindPath(APath* path)
//{
//
//	UE_LOG(LogTemp, Warning, TEXT("FindPath"));
//
//	if (!FoundActor)
//	{
//		return;
//	}
//
//	UE_LOG(LogTemp, Warning, TEXT("FindPath Success"));
//
//
//	USplineComponent* Spline = FoundActor->SplineComp; //Cast<USplineComponent>(FoundActor);
//
//	// ���� �󿡼� ��ġ�� ����
//	FVector TangentLoc = GetActorLocation();
//
//	// ���ö����� ���� ������ ������� ���� ������ ������� ����
//	ESplineCoordinateSpace::Type CoordinateSpace = ESplineCoordinateSpace::World; // ����Ϸ��� ��ǥ ���� ����
//
//	// ���� ����� ��ġ�� ź��Ʈ�� �˻� - �̵������� �����ϴ� �κ�
//	FVector ClosestTangent = Spline->FindTangentClosestToWorldLocation(TangentLoc, CoordinateSpace);
//
//	//FVector SplineLoc = ClosestTangent.Normalize() * 1000.f + GetActorLocation();
//	FVector SplineLoc = GetActorLocation() + ClosestTangent.GetSafeNormal() * 1000.f;
//
//	// ���� ����� ���ö��� ��ġ�� �˻�
//	FVector ClosestLocation = Spline->FindLocationClosestToWorldLocation(SplineLoc, CoordinateSpace);
//
//	FVector Start = GetActorLocation();
//	FVector Target = ClosestLocation;
//
//	FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(Start, Target);
//
//	FRotator A = GetActorRotation();
//	FRotator B = LookAtRotation;
//
//	// NormalizedDeltaRotator �Լ��� ȣ���Ͽ� �� ȸ������ ���̸� ����ȭ�� ���� ã���ϴ�.
//	FRotator DeltaRotator = UKismetMathLibrary::NormalizedDeltaRotator(A, B);
//
//	// ������ �Է� ���� �Է� ������ �����մϴ�.
//	float Value = DeltaRotator.Yaw; // �Է� ��
//	float InRangeA = 45.0f; // �Է� ������ ���� ��
//	float InRangeB = -45.0f; // �Է� ������ �� ��
//
//	// ��� ������ �����մϴ�.
//	float OutRangeA = -1.0f; // ��� ������ ���� ��
//	float OutRangeB = 1.0f; // ��� ������ �� ��
//
//	// MapRangeClamped �Լ��� ȣ���Ͽ� �Է� ���� ��� ������ �����մϴ�.
//	MappedValue = UKismetMathLibrary::MapRangeClamped(Value, InRangeA, InRangeB, OutRangeA, OutRangeB);
//
//
//}



