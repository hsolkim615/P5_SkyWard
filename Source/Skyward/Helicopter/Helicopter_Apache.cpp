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
#include <../../../../../../../Source/Runtime/UMG/Public/Components/WidgetComponent.h>
#include "../Component/HeliComp/HeliSystemComp.h"
#include "../GameModeBase/SkywardGameModeBase.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h>

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
	MGEffectComp->SetActive(false);

	// ī�޶� ��ġ ������Ʈ
	CameraLocComp = CreateDefaultSubobject<USceneComponent>(TEXT("CameraLocComp"));
	CameraLocComp->SetupAttachment(RootComponent);
	CameraLocComp->SetRelativeLocation(FVector(245, 0, 100)/*FVector(270, 0, 245)*/);

	// ī�޶� ������Ʈ
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(CameraLocComp);

	// Info UI ������Ʈ 
	HeliInfoUIComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("HeliInfoUIComp"));
	HeliInfoUIComp->SetupAttachment(RootComponent);
	HeliInfoUIComp->SetRelativeLocation(FVector(370, 0, 245));
	HeliInfoUIComp->SetRelativeRotation(FRotator(0, 180, 0));
	HeliInfoUIComp->SetRelativeScale3D(FVector(0.11f));
	HeliInfoUIComp->SetDrawSize(FVector2D(1000.f));

	// �̼� UI ������Ʈ
	MissionUIComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("MissionUIComp"));
	MissionUIComp->SetupAttachment(RootComponent);
	MissionUIComp->SetRelativeLocation(FVector(340, 0, 235));
	MissionUIComp->SetRelativeScale3D(FVector(0.05f));
	MissionUIComp->SetDrawSize(FVector2D(1000));

	// �̵� ������Ʈ
	MoveComp = CreateDefaultSubobject<UHeliMoveComp>(TEXT("MoveComp"));

	// ���� ������Ʈ
	AttackComp = CreateDefaultSubobject<UHeliAttackComp>(TEXT("AttackComp"));

	// ���� ������Ʈ
	SoundComp = CreateDefaultSubobject<UHeliSoundComp>(TEXT("SoundComp"));

	// �ý��� ������Ʈ
	SystemComp = CreateDefaultSubobject<UHeliSystemComp>(TEXT("SystemComp"));

	// ----------------------

	StateComponent = CreateDefaultSubobject<UStateComponent>(TEXT("StateComponent"));




	GameEndUI1 = CreateDefaultSubobject<UWidgetComponent>(TEXT("GameEndUI1"));
	GameEndUI1->SetupAttachment(RootComponent);
	GameEndUI1->SetVisibility(false);
	GameEndUI1->SetRelativeLocation(FVector(340, 0, 235));
	GameEndUI1->SetRelativeRotation(FRotator(0, 180, 0));
	GameEndUI1->SetRelativeScale3D(FVector(0.04f));
	GameEndUI1->SetDrawSize(FVector2D(2000, 1000));

	GameEndUI2 = CreateDefaultSubobject<UWidgetComponent>(TEXT("GameEndUI2"));
	GameEndUI2->SetupAttachment(RootComponent);
	GameEndUI2->SetVisibility(false);
	GameEndUI2->SetRelativeLocation(FVector(310, 0, 260));
	GameEndUI2->SetRelativeRotation(FRotator(-60, 180, 0));
	GameEndUI2->SetRelativeScale3D(FVector(0.04f));
	GameEndUI2->SetDrawSize(FVector2D(2000, 1000));

	GameEndUI3 = CreateDefaultSubobject<UWidgetComponent>(TEXT("GameEndUI3"));
	GameEndUI3->SetupAttachment(RootComponent);
	GameEndUI3->SetVisibility(false);
	GameEndUI3->SetRelativeLocation(FVector(300, 60, 230));
	GameEndUI3->SetRelativeRotation(FRotator(0, 270, 20));
	GameEndUI3->SetRelativeScale3D(FVector(0.04f));
	GameEndUI3->SetDrawSize(FVector2D(2000, 1000));

	GameEndUI4 = CreateDefaultSubobject<UWidgetComponent>(TEXT("GameEndUI4"));
	GameEndUI4->SetupAttachment(RootComponent);
	GameEndUI4->SetVisibility(false);
	GameEndUI4->SetRelativeLocation(FVector(300, -60, 230));
	GameEndUI4->SetRelativeRotation(FRotator(0, 90, -20));
	GameEndUI4->SetRelativeScale3D(FVector(0.04f));
	GameEndUI4->SetDrawSize(FVector2D(2000, 1000));


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

	SkywardGM = Cast<ASkywardGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	//StateComponent->SetMaxHealthPoint(1000.f);
	//StateComponent->SetAttackDamage(10.f);

	ModifyMapping(true);

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

/*
void AHelicopter_Apache::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

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

}
	*/

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

void AHelicopter_Apache::SetDoor()
{
	if (bIsOpenDoor == true) {

	}
	else if (bIsOpenDoor == false) {

	}
}

void AHelicopter_Apache::Damaged()
{

}

void AHelicopter_Apache::Die()
{
	// ���� ����
	// ������ ������ �й� UI�� ����� ��

	SkywardGM->bIsFail = true;
	SkywardGM->bIsSuccess= false;

	// ���� ���� �Ҹ�
	if (LoseSound) {
		UGameplayStatics::PlaySound2D(GetWorld(), LoseSound);
	}

	HeliInfoUIComp->SetVisibility(false);
	MissionUIComp->SetVisibility(false);


	GameEndUI1->SetVisibility(true);
	GameEndUI2->SetVisibility(true);
	GameEndUI3->SetVisibility(true);
	GameEndUI4->SetVisibility(true);

}
