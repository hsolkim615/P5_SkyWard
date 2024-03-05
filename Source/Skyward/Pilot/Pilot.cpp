// Fill out your copyright notice in the Description page of Project Settings.


#include "../Pilot/Pilot.h"
#include <MotionControllerComponent.h>
#include <Camera/CameraComponent.h>
#include <EnhancedInputComponent.h>
#include <HeadMountedDisplayFunctionLibrary.h>
#include <EnhancedInputSubsystems.h>
#include "../Helicopter/HelicopterBase.h"

// Sets default values
APilot::APilot()
{
	// Set this character to call Tick() every frame.  SYou can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// ������ ��Ʈ�ѷ�
	RightController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("RightController"));
	RightController->SetupAttachment(RootComponent);
	RightController->SetTrackingMotionSource(FName("Right")); // �����տ� ��ġ

	RightHandMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("RightHandMesh"));
	RightHandMesh->SetupAttachment(RightController);
	RightHandMesh->SetRelativeRotation(FRotator(0, 0, 90));

	// �޼� ��Ʈ�ѷ�
	LeftController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("LeftController"));
	LeftController->SetupAttachment(RootComponent);
	LeftController->SetTrackingMotionSource(FName("Left"));// �޼տ� ��ġ

	LeftHandMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("LeftHandMesh"));
	LeftHandMesh->SetupAttachment(LeftController);
	LeftHandMesh->SetRelativeRotation(FRotator(0, -180, 90));

	// ī�޶� ������Ʈ
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void APilot::BeginPlay()
{
	Super::BeginPlay();

	// VR Ʈ��ŷ �� IMC ����
	ModifyMapping(true);

}



// Called every frame
void APilot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Player �̵�================================
	PilotDirection.Normalize();

	FTransform ControllerTransform = FTransform(this->GetControlRotation());

	FVector dir = ControllerTransform.TransformVector(PilotDirection);

	this->AddMovementInput(dir * 0.5f);

	PilotDirection = FVector::ZeroVector;
	// Player �̵�================================

}

// Called to bind functionality to input
void APilot::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (EnhancedInputComponent) {
		EnhancedInputComponent->BindAction(IA_Pilot_Move, ETriggerEvent::Triggered, this, &APilot::Pilot_Move);

		EnhancedInputComponent->BindAction(IA_Pilot_Turn, ETriggerEvent::Triggered, this, &APilot::Pilot_Turn);

		EnhancedInputComponent->BindAction(IA_Pilot_LineTrace, ETriggerEvent::Triggered, this, &APilot::Pilot_LineTrace);

		EnhancedInputComponent->BindAction(IA_Pilot_TakeHeli, ETriggerEvent::Started, this, &APilot::Pilot_TakeHeli);

	}

}
void APilot::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	ModifyMapping(true);

}

void APilot::UnPossessed()
{
	Super::UnPossessed();

	ModifyMapping(false);

}

void APilot::Pilot_Move(const FInputActionValue& value)
{
	FVector2D InputDirection = value.Get<FVector2D>();

	PilotDirection.X = InputDirection.Y;
	PilotDirection.Y = InputDirection.X;

}

void APilot::Pilot_Turn(const FInputActionValue& value)
{
	float PlayerRotation = 0.3f * value.Get<float>();

	AddControllerYawInput(PlayerRotation);

}

void APilot::Pilot_LineTrace(const FInputActionValue& value)
{
	bool bValue = value.Get<bool>();

	// ����Ʈ���̽��� ��ư Ŭ��

}

void APilot::Pilot_TakeHeli(const FInputActionValue& value)
{
	bool TakeHeil = value.Get<bool>();

	// � ���ͳ� ������Ʈ Ŭ������ �̸��� �����մϴ�.
	TSubclassOf<AHelicopterBase> ClassFilter;

	// �������� ������ ����� ������ �迭�� ����ϴ�.
	TArray<AActor*> OverlappingActors;

	// ���� ������ ������Ʈ���� �������� ���͸� �����ɴϴ�.
	GetOverlappingActors(OverlappingActors, ClassFilter);

	// �������� ���͸� ��ȸ�ϸ鼭 �︮���͸� ã���ϴ�.
	for (AActor* OverlappingActor : OverlappingActors) {
		AHelicopterBase* Helicopter = Cast<AHelicopterBase>(OverlappingActor);
		if (Helicopter) {
			// �︮���͸� ã�����Ƿ� �÷��̾� ĳ���͸� �︮���ͷ� �����մϴ�.
			APlayerController* PlayerController = Cast<APlayerController>(GetController());
			if (PlayerController) {
				PlayerController->Possess(Helicopter);
			}
			break; // �︮���͸� ã�����Ƿ� �� �̻� �ݺ��� �ʿ䰡 �����ϴ�.
		}
	}

}

void APilot::ModifyMapping(bool bAddMapping)
{
	UHeadMountedDisplayFunctionLibrary::SetTrackingOrigin(EHMDTrackingOrigin::Stage);

	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		UEnhancedInputLocalPlayerSubsystem* subsys = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

		if (subsys != nullptr && IMC_Pilot != nullptr)
		{
			if (bAddMapping)
			{
				subsys->AddMappingContext(IMC_Pilot, 0);
			}
			else
			{
				subsys->RemoveMappingContext(IMC_Pilot);
			}
		}
	}

}
