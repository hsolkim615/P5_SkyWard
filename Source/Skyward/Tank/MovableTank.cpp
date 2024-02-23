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

	//// UKismetSystemLibrary::Delay를 호출하여 지연을 설정합니다.
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

	// 월드 상에서 위치를 정의
	FVector TangentLoc = GetActorLocation();

	// 스플라인의 로컬 공간을 사용할지 월드 공간을 사용할지 지정
	ESplineCoordinateSpace::Type CoordinateSpace = ESplineCoordinateSpace::World; // 사용하려는 좌표 공간 선택

	// 가장 가까운 위치의 탄젠트를 검색
	FVector ClosestTangent = Spline->FindTangentClosestToWorldLocation(TangentLoc, CoordinateSpace);

	//FVector SplineLoc = ClosestTangent.Normalize() * 1000.f + GetActorLocation();
	FVector SplineLoc = GetActorLocation() + ClosestTangent.GetSafeNormal() * 1000.f;

	// 가장 가까운 스플라인 위치를 검색
	FVector ClosestLocation = Spline->FindLocationClosestToWorldLocation(SplineLoc, CoordinateSpace);

	FVector Start = GetActorLocation();
	FVector Target = ClosestLocation;

	FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(Start, Target);

	FRotator A = GetActorRotation();
	FRotator B = LookAtRotation;

	// NormalizedDeltaRotator 함수를 호출하여 두 회전값의 차이를 정규화한 값을 찾습니다.
	FRotator DeltaRotator = UKismetMathLibrary::NormalizedDeltaRotator(A, B);

	// 매핑할 입력 값과 입력 범위를 정의합니다.
	float Value = DeltaRotator.Yaw; // 입력 값
	float InRangeA = 45.0f; // 입력 범위의 시작 값
	float InRangeB = -45.0f; // 입력 범위의 끝 값

	// 출력 범위를 정의합니다.
	float OutRangeA = -1.0f; // 출력 범위의 시작 값
	float OutRangeB = 1.0f; // 출력 범위의 끝 값

	// MapRangeClamped 함수를 호출하여 입력 값을 출력 범위로 매핑합니다.
	MappedValue = UKismetMathLibrary::MapRangeClamped(Value, InRangeA, InRangeB, OutRangeA, OutRangeB);

}



