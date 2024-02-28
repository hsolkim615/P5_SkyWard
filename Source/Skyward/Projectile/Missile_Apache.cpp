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

	// �Ѿ� ����
	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(RootComponent);

	NSComp = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NSComp"));
	NSComp->SetupAttachment(RootComponent);
	NSComp->SetRelativeLocation(FVector(-150, 0, 0));

}

void AMissile_Apache::BeginPlay()
{
	Super::BeginPlay();


	// HitCollision�� overlap�Ǿ��� �� ȣ��
	HitCollision->OnComponentBeginOverlap.AddDynamic(this, &AMissile_Apache::OnOverlapBegin);

	NSComp->SetActive(false);

	//TraceChannel = ECollisionChannel::ECC_Visibility; // ���� Ʈ���̽��� ä�� ����
	//CollisionParams.AddIgnoredActor(this); // this�� ���� ������ �����͸� ��Ÿ���ϴ�.
}

void AMissile_Apache::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (EngineOn == false) {
		return;
	}

	// ��ǥ ��ġ�� �̵��ϴ� ���� ���� ���
	FVector Direction = (TargetLocation - InitialLocation).GetSafeNormal();

	// ���� �ӵ��� �ִ� �ӵ����� ���� �� ����
	if (CurrentSpeed < MaxSpeed) {
		CurrentSpeed += MissileAcceleration * DeltaTime;
	}

	// ��ǥ ��ġ �������� �̵�
	FVector NewLocation = GetActorLocation() + Direction * CurrentSpeed * DeltaTime;
	SetActorLocation(NewLocation);

	// ========================================================================
	/*
	// ��ǥ ���� ���� ���
	FVector Direction = (TargetLocation - InitialLocation).GetSafeNormal();

	// �ʱ� �ӵ�
	FVector InitialVelocity = Direction * InitialSpeed;

	// ���ӵ�
	FVector Acceleration = Direction * MissileAcceleration;

	// ���� ��ġ ���
	FVector CurrentLocation = GetActorLocation();

	// ��� �ð� ����
	float ElapsedTime = CurrentSpeed / InitialSpeed;  // ��� �ð��� �ʱ� �ӵ��� ���� �ӵ��� ������ ���
	FVector NewLocation = CurrentLocation + InitialVelocity * ElapsedTime + 0.5f * Acceleration * FMath::Square(ElapsedTime);

	// ���� �ӵ� ����
	CurrentSpeed += MissileAcceleration * DeltaTime;

	// ���ο� ��ġ ����
	SetActorLocation(NewLocation);
	*/

	/*
	// ��ǥ ��ġ�� �ε巴�� �̵�
	FVector CurrentLocation = GetActorLocation();
	FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, 2000.f);
	SetActorLocation(NewLocation);
	*/

	/*
	// ���� �ӵ��� �ִ� �ӵ����� ���� �� ����
	if (CurrentSpeed < MaxSpeed) {
		CurrentSpeed += MissileAcceleration * DeltaTime;
	}

	// ��ǥ ��ġ�� �ε巴�� �̵�
	FVector CurrentLocation = GetActorLocation();
	FVector Direction = (TargetLocation - CurrentLocation).GetSafeNormal();
	FVector NewLocation = CurrentLocation + Direction * CurrentSpeed * DeltaTime;
	SetActorLocation(NewLocation);
	*/




	/*
	if (bAttack == true) {
		return;
	}

	// ���ݱ�� ���� Ʈ���̽� ����
	StartLocation = this->GetActorLocation();// ���� ��ġ ����
	EndLocation = StartLocation + this->GetActorForwardVector() * 20; // ���� ��ġ ����

	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, TraceChannel, CollisionParams)) {


		//DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, false, 5.0f, 0, 5.0f);

		UE_LOG(LogTemp, Warning, TEXT("AMissile_Apache::Tick) Tick Actor : %s"), * HitResult.GetActor()->GetActorNameOrLabel());

		bAttack = true;

		if (HitResult.GetActor() && HitResult.GetActor()->IsA<ATankBase>()) {

			//FRotator MissileDirection = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TargetLocation);

			//SetActorRelativeRotation(MissileDirection);

			UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), NSBoom, GetActorLocation(), FRotator(0), FVector(5));

			// ***** �������� �ִ� ������� ���� �ʿ� / ��ũ�� ���� �ִ� StateCompoenet�� �Լ��� ȣ���� ��
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

		// ***** �������� �ִ� ������� ���� �ʿ� / ��ũ�� ���� �ִ� StateCompoenet�� �Լ��� ȣ���� ��
		OtherActor->Destroy();

		Destroy();

	}
	*/

}

void AMissile_Apache::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if (OtherComp) {
		FString OtherObjectName = OtherComp->GetOwner()->GetName();

		// �浹�� ����� �̸��� �α׿� ���
		UE_LOG(LogTemp, Warning, TEXT("Collision with: %s"), *OtherObjectName);


	}
	/*
	if (OtherActor) {

		FString OtherActorName = OtherActor->GetOwner()->GetName();

		// �浹�� ����� �̸��� �α׿� ���
		UE_LOG(LogTemp, Warning, TEXT("Collision with: %s"), *OtherActorName);

	}
	*/


	BoomMissile();

	/*
	// �浹�� ������Ʈ�� �浹 ä�� Ȯ��
	ECollisionChannel CollisionChannel = OtherComp->GetCollisionObjectType();

	// �浹�� ������Ʈ�� �浹 ä��Ȯ��
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

	// ����Ʈ ����

}

void AMissile_Apache::BoomMissile()
{

	TArray<AActor*> OverlappingActors;
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	TArray<AActor*> ActorsToIgnore;

	UKismetSystemLibrary::CapsuleOverlapActors(GetWorld(), // ���� ���ؽ�Ʈ ��ü
		GetActorLocation(), // Capsule�� ��ġ
		2000.f, // Capsule�� ������
		2000.f, // Capsule�� �� ����
		ObjectTypes, // �浹 ��� ��ü ����
		nullptr, // ���� Ŭ���� ����
		ActorsToIgnore, // ������ ���͵��� �迭
		OverlappingActors // ����� ������ �迭
	);

	// ����Ʈ ����
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), NSBoom, GetActorLocation(), FRotator(0), FVector(7));

	DrawDebugCapsule(GetWorld(), GetActorLocation(), 2000.f, 2000.f, FQuat::Identity, FColor::Blue, false, 30.0f, 0, 2.0f);

	if (OverlappingActors.Num() > 0) {
		for (AActor* Actor : OverlappingActors) {

			if (Actor->IsA<ATankBase>()) {

				// StateComponent�� �̿��� ü���� ���ҽ�Ű�� ������� ����

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

