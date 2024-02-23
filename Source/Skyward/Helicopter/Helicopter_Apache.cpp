// Fill out your copyright notice in the Description page of Project Settings.
#include "../Helicopter/Helicopter_Apache.h"
#include <HeadMountedDisplayFunctionLibrary.h>
#include <EnhancedInputSubsystems.h>
#include "../Component/HeliComp/HeliMoveComp.h"
#include "../Component/HeliComp/HeliSoundComp.h"
#include "../Component/StateComponent.h"
#include <MotionControllerComponent.h>
#include <Camera/CameraComponent.h>
#include <Components/BoxComponent.h>
#include <Components/SkeletalMeshComponent.h>
#include "../Pilot/Pilot.h"
#include "../Component/HeliComp/HeliAttackComp.h"
#include "../Component/HeliComp/HeliTestComp.h"
#include <Components/SceneComponent.h>
#include <../../../../../../../Source/Runtime/Engine/Classes/Particles/ParticleSystemComponent.h>

AHelicopter_Apache::AHelicopter_Apache()
{
	PrimaryActorTick.bCanEverTick = true;

	// ������ ��Ʈ�ѷ�
	RightController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("RightController"));
	RightController->SetupAttachment(RootComponent);
	RightController->SetTrackingMotionSource(FName("Right")); // �����տ� ��ġ


	// �޼� ��Ʈ�ѷ�
	LeftController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("LeftController"));
	LeftController->SetupAttachment(RootComponent);
	LeftController->SetTrackingMotionSource(FName("Left"));// �޼տ� ��ġ


	// ž�±� 
	DoorCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	DoorCollision->SetupAttachment(RootComponent);
	DoorCollision->SetBoxExtent(FVector(80, 60, 180));
	DoorCollision->SetRelativeLocation(FVector(290, 250, 180));

	// ����� �ѿ�
	MGNozzleComp = CreateDefaultSubobject<USceneComponent>(TEXT("NozzleComp"));
	MGNozzleComp->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName("gun_tilt_jntSocket"));

	// ����� ����Ʈ
	MGEffectComp = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MGEffectComp"));
	MGEffectComp->SetupAttachment(MGNozzleComp);

	// ī�޶� ��ġ ������Ʈ
	CameraLocComp = CreateDefaultSubobject<USceneComponent>(TEXT("CameraLocComp"));
	CameraLocComp->SetupAttachment(RootComponent);
	CameraLocComp->SetRelativeLocation(FVector(245, 0, 100)/*FVector(270, 0, 245)*/);

	// ī�޶� ������Ʈ
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(CameraLocComp);

	// �̵� ������Ʈ
	MoveComp = CreateDefaultSubobject<UHeliMoveComp>(TEXT("MoveComp"));

	// ���� ������Ʈ
	AttackComp = CreateDefaultSubobject<UHeliAttackComp>(TEXT("AttackComp"));

	// ���� ������Ʈ
	SoundComp = CreateDefaultSubobject<UHeliSoundComp>(TEXT("SoundComp"));



	// ----------------------

	StateComponent = CreateDefaultSubobject<UStateComponent>(TEXT("StateComponent"));


	// =======================

	// Test ������Ʈ
	TestComp = CreateDefaultSubobject<UHeliTestComp>(TEXT("TestComp"));

}

void AHelicopter_Apache::BeginPlay()
{
	Super::BeginPlay();

	// EnhancedInput ���� ���� - IMC_Heli ===================================================
	//ModifyMapping(true);

	//DoorCollision->OnComponentBeginOverlap.AddDynamic(this, &AHelicopter_Apache::OnOverlapBegin);

	StateComponent->SetMaxHealthPoint(1000.f);
	StateComponent->SetAttackDamage(10.f);

}

void AHelicopter_Apache::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

void AHelicopter_Apache::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	ModifyMapping(true);

}

void AHelicopter_Apache::UnPossessed()
{
	Super::UnPossessed();

	ModifyMapping(false);

}

void AHelicopter_Apache::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	OnSetupInputDelegate.Broadcast(PlayerInputComponent);

}

void AHelicopter_Apache::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	/*
	if (!OtherActor) {
		return;
	}

	if (OtherActor->IsA<APilot>()) {

		DoorCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		
		EnableInput(GetWorld()->GetFirstPlayerController());

		HeliOtherActor = OtherActor;

		HeliOtherActor->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
		
		GetWorld()->GetFirstPlayerController()->UnPossess();

		GetWorld()->GetFirstPlayerController()->Possess(this);


	}
	*/

}

void AHelicopter_Apache::ModifyMapping(bool bAddMapping)
{
	
	UHeadMountedDisplayFunctionLibrary::SetTrackingOrigin(EHMDTrackingOrigin::Stage);

	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		UEnhancedInputLocalPlayerSubsystem* subsys = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

		if (subsys != nullptr && IMC_Heli != nullptr)
		{
			if (bAddMapping)
			{
				subsys->AddMappingContext(IMC_Heli, 0);
			}
			else
			{
				subsys->RemoveMappingContext(IMC_Heli);
			}
		}
	}

}
