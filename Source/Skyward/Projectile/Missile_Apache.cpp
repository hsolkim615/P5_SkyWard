// Fill out your copyright notice in the Description page of Project Settings.


#include "../Projectile/Missile_Apache.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Components/SphereComponent.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Components/SkeletalMeshComponent.h>
#include "../Helicopter/Helicopter_Apache.h"
#include "../Tank/TankBase.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/KismetMathLibrary.h>
#include <../../../../../../../Plugins/FX/Niagara/Source/Niagara/Public/NiagaraComponent.h>
#include <../../../../../../../Plugins/FX/Niagara/Source/Niagara/Public/NiagaraFunctionLibrary.h>
#include <../../../../../../../Plugins/FX/Niagara/Source/Niagara/Classes/NiagaraSystem.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/GameFramework/Actor.h>
#include "../Buliding/Bunker.h"

AMissile_Apache::AMissile_Apache()
{
	PrimaryActorTick.bCanEverTick = true;

	HitCollision = CreateDefaultSubobject<USphereComponent>(TEXT("HitCollision"));
	SetRootComponent(HitCollision);

	// 총알 외형
	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(RootComponent);

	NSComp = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NSComp"));
	NSComp->SetupAttachment(RootComponent);
	NSComp->SetRelativeLocation(FVector(-150, 0, 0));

}

void AMissile_Apache::BeginPlay()
{
	Super::BeginPlay();


	// HitCollision과 overlap되었을 때 호출
	HitCollision->OnComponentBeginOverlap.AddDynamic(this, &AMissile_Apache::OnOverlapBegin);

	NSComp->SetActive(false);

	//TraceChannel = ECollisionChannel::ECC_Visibility; // 라인 트레이스할 채널 설정
	//CollisionParams.AddIgnoredActor(this); // this는 현재 액터의 포인터를 나타냅니다.
}

void AMissile_Apache::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (EngineOn == false) {
		return;
	}

	// 목표 위치로 이동하는 방향 벡터 계산
	FVector Direction = (TargetLocation - InitialLocation).GetSafeNormal();

	// 현재 속도가 최대 속도보다 작을 때 가속
	if (CurrentSpeed < MaxSpeed) {
		CurrentSpeed += MissileAcceleration * DeltaTime;
	}

	// 목표 위치 방향으로 이동
	FVector NewLocation = GetActorLocation() + Direction * CurrentSpeed * DeltaTime;
	SetActorLocation(NewLocation);

	// ========================================================================
	/*
	// 목표 방향 벡터 계산
	FVector Direction = (TargetLocation - InitialLocation).GetSafeNormal();

	// 초기 속도
	FVector InitialVelocity = Direction * InitialSpeed;

	// 가속도
	FVector Acceleration = Direction * MissileAcceleration;

	// 현재 위치 계산
	FVector CurrentLocation = GetActorLocation();

	// 경과 시간 적용
	float ElapsedTime = CurrentSpeed / InitialSpeed;  // 경과 시간은 초기 속도와 현재 속도의 비율로 계산
	FVector NewLocation = CurrentLocation + InitialVelocity * ElapsedTime + 0.5f * Acceleration * FMath::Square(ElapsedTime);

	// 현재 속도 갱신
	CurrentSpeed += MissileAcceleration * DeltaTime;

	// 새로운 위치 설정
	SetActorLocation(NewLocation);
	*/

	/*
	// 목표 위치로 부드럽게 이동
	FVector CurrentLocation = GetActorLocation();
	FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, 2000.f);
	SetActorLocation(NewLocation);
	*/

	/*
	// 현재 속도가 최대 속도보다 작을 때 가속
	if (CurrentSpeed < MaxSpeed) {
		CurrentSpeed += MissileAcceleration * DeltaTime;
	}

	// 목표 위치로 부드럽게 이동
	FVector CurrentLocation = GetActorLocation();
	FVector Direction = (TargetLocation - CurrentLocation).GetSafeNormal();
	FVector NewLocation = CurrentLocation + Direction * CurrentSpeed * DeltaTime;
	SetActorLocation(NewLocation);
	*/




	/*
	if (bAttack == true) {
		return;
	}

	// 공격기능 라인 트레이스 실행
	StartLocation = this->GetActorLocation();// 시작 위치 설정
	EndLocation = StartLocation + this->GetActorForwardVector() * 20; // 종료 위치 설정

	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, TraceChannel, CollisionParams)) {


		//DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, false, 5.0f, 0, 5.0f);

		UE_LOG(LogTemp, Warning, TEXT("AMissile_Apache::Tick) Tick Actor : %s"), * HitResult.GetActor()->GetActorNameOrLabel());

		bAttack = true;

		if (HitResult.GetActor() && HitResult.GetActor()->IsA<ATankBase>()) {

			//FRotator MissileDirection = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TargetLocation);

			//SetActorRelativeRotation(MissileDirection);

			UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), NSBoom, GetActorLocation(), FRotator(0), FVector(5));

			// ***** 데미지를 주는 방식으로 수정 필요 / 탱크가 갖고 있는 StateCompoenet의 함수를 호출할 것
			HitResult.GetActor()->Destroy();

			Destroy();

		}
		else if (HitResult.GetActor() && HitResult.GetActor()->IsA<AMissile_Apache>()) {

			bAttack = false;

		}
		else if (HitResult.GetActor() && HitResult.GetActor()->IsA<AHelicopter_Apache>()) {

			bAttack = false;

		}
		else {

			UE_LOG(LogTemp, Warning, TEXT("Boom"));


			UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), NSBoom, GetActorLocation(), FRotator(0), FVector(5));

			Destroy();

		}

	}
	*/

}

void AMissile_Apache::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);


	//BoomMissile();

	/*
	if (OtherActor->IsA<ATankBase>()) {

		FRotator MissileDirection = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TargetLocation);

		SetActorRelativeRotation(MissileDirection);

		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), NSBoom, GetActorLocation(), FRotator(0), FVector(5));

		// ***** 데미지를 주는 방식으로 수정 필요 / 탱크가 갖고 있는 StateCompoenet의 함수를 호출할 것
		OtherActor->Destroy();

		Destroy();

	}
	*/

}

void AMissile_Apache::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if (OtherComp) {
		FString OtherObjectName = OtherComp->GetOwner()->GetName();

		// 충돌한 대상의 이름을 로그에 출력
		UE_LOG(LogTemp, Warning, TEXT("Collision with: %s"), *OtherObjectName);


	}
	/*
	if (OtherActor) {

		FString OtherActorName = OtherActor->GetOwner()->GetName();

		// 충돌한 대상의 이름을 로그에 출력
		UE_LOG(LogTemp, Warning, TEXT("Collision with: %s"), *OtherActorName);

	}
	*/


	BoomMissile();

	/*
	// 충돌한 오브젝트의 충돌 채널 확인
	ECollisionChannel CollisionChannel = OtherComp->GetCollisionObjectType();

	// 충돌한 오브젝트의 충돌 채널확인
	if (CollisionChannel == ECC_WorldStatic)
	{

		BoomMissile();


	}
	*/
}

void AMissile_Apache::SaveOwner()
{
	Apache = Cast<AHelicopter_Apache>(GetOwner());

}

void AMissile_Apache::MissileMove(FVector TargetLoc)
{
	TargetLocation = TargetLoc;

	EngineOn = true;

	// 이펙트 연출

}

void AMissile_Apache::BoomMissile()
{

	TArray<AActor*> OverlappingActors;
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	TArray<AActor*> ActorsToIgnore;

	UKismetSystemLibrary::CapsuleOverlapActors(GetWorld(), // 월드 컨텍스트 객체
		GetActorLocation(), // Capsule의 위치
		2000.f, // Capsule의 반지름
		2000.f, // Capsule의 반 높이
		ObjectTypes, // 충돌 허용 객체 유형
		nullptr, // 액터 클래스 필터
		ActorsToIgnore, // 무시할 액터들의 배열
		OverlappingActors // 결과를 저장할 배열
	);

	// 이펙트 연출
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), NSBoom, GetActorLocation(), FRotator(0), FVector(7));

	DrawDebugCapsule(GetWorld(), GetActorLocation(), 2000.f, 2000.f, FQuat::Identity, FColor::Blue, false, 30.0f, 0, 2.0f);

	if (OverlappingActors.Num() > 0) {
		for (AActor* Actor : OverlappingActors) {

			if (Actor->IsA<ATankBase>()) {

				// StateComponent를 이용해 체력을 감소시키는 방식으로 수정

				Actor->Destroy();

			}
			else if (Actor->IsA<ABunker>()) {
				Actor->Destroy();
			}

		}
	}


	Destroy();

}

void AMissile_Apache::SetInitialLocation()
{
	InitialLocation = GetActorLocation();
}

