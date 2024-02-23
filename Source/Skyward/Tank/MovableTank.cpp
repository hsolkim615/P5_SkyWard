// Fill out your copyright notice in the Description page of Project Settings.


#include "../Tank/MovableTank.h"
#include "../Wheel/Wheel_MovableTank.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include "../Actor/Path.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Components/SplineComponent.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/KismetMathLibrary.h>
#include <ChaosWheeledVehicleMovementComponent.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h>

AMovableTank::AMovableTank()
{
	ChaosWheeledVehicleMovementComponent = CreateDefaultSubobject<UChaosWheeledVehicleMovementComponent>(TEXT("ChaosWheeledVehicleMovementComponent"));
}

// Called when the game starts or when spawned
void AMovableTank::BeginPlay()
{
	Super::BeginPlay();



	FoundActor = Cast<APath>(UGameplayStatics::GetActorOfClass(GetWorld(), APath::StaticClass()));

	ChaosWheeledVehicleMovementComponent->SetThrottleInput(1.0f);

	//UObject* WorldContextObject = GetWorld(); 
	//float DelayDuration = 3.0f; 
	//FLatentActionInfo LatentInfo;

	//// UKismetSystemLibrary::Delay�� ȣ���Ͽ� ������ �����մϴ�.
	//UKismetSystemLibrary::Delay(WorldContextObject, DelayDuration, LatentInfo);
	//UKismetSystemLibrary::Delay(WorldContextObject, DelayDuration, LatentInfo,
	//	[](const FLatentActionInfo& LatentInfo) {
	//		ChaosWheeledVehicleMovementComponent->SetThrottleInput(0.5f);
	//	}
	//);
}

// Called every frame
void AMovableTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	this->FindPath(FoundActor);

	/*if (ChaosWheeledVehicleMovementComponent)
	{
		ChaosWheeledVehicleMovementComponent->SetSteeringInput(MappedValue);
	}*/

	ChaosWheeledVehicleMovementComponent->SetSteeringInput(MappedValue);

}

void AMovableTank::FindPath(APath* path)
{

	USplineComponent* Spline = FoundActor->SplineComp; //Cast<USplineComponent>(FoundActor);

	// ���� �󿡼� ��ġ�� ����
	FVector TangentLoc = GetActorLocation();

	// ���ö����� ���� ������ ������� ���� ������ ������� ����
	ESplineCoordinateSpace::Type CoordinateSpace = ESplineCoordinateSpace::World; // ����Ϸ��� ��ǥ ���� ����

	// ���� ����� ��ġ�� ź��Ʈ�� �˻�
	FVector ClosestTangent = Spline->FindTangentClosestToWorldLocation(TangentLoc, CoordinateSpace);

	//FVector SplineLoc = ClosestTangent.Normalize() * 1000.f + GetActorLocation();
	FVector SplineLoc = GetActorLocation() + ClosestTangent.GetSafeNormal() * 1000.f;

	// ���� ����� ���ö��� ��ġ�� �˻�
	FVector ClosestLocation = Spline->FindLocationClosestToWorldLocation(SplineLoc, CoordinateSpace);

	FVector Start = GetActorLocation();
	FVector Target = ClosestLocation;

	FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(Start, Target);

	FRotator A = GetActorRotation();
	FRotator B = LookAtRotation;

	// NormalizedDeltaRotator �Լ��� ȣ���Ͽ� �� ȸ������ ���̸� ����ȭ�� ���� ã���ϴ�.
	FRotator DeltaRotator = UKismetMathLibrary::NormalizedDeltaRotator(A, B);

	// ������ �Է� ���� �Է� ������ �����մϴ�.
	float Value = DeltaRotator.Yaw; // �Է� ��
	float InRangeA = 45.0f; // �Է� ������ ���� ��
	float InRangeB = -45.0f; // �Է� ������ �� ��

	// ��� ������ �����մϴ�.
	float OutRangeA = -1.0f; // ��� ������ ���� ��
	float OutRangeB = 1.0f; // ��� ������ �� ��

	// MapRangeClamped �Լ��� ȣ���Ͽ� �Է� ���� ��� ������ �����մϴ�.
	MappedValue = UKismetMathLibrary::MapRangeClamped(Value, InRangeA, InRangeB, OutRangeA, OutRangeB);

}



