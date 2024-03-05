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

	// 오른손 컨트롤러
	RightController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("RightController"));
	RightController->SetupAttachment(RootComponent);
	RightController->SetTrackingMotionSource(FName("Right")); // 오른손에 매치

	RightHandMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("RightHandMesh"));
	RightHandMesh->SetupAttachment(RightController);
	RightHandMesh->SetRelativeRotation(FRotator(0, 0, 90));

	// 왼손 컨트롤러
	LeftController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("LeftController"));
	LeftController->SetupAttachment(RootComponent);
	LeftController->SetTrackingMotionSource(FName("Left"));// 왼손에 매치

	LeftHandMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("LeftHandMesh"));
	LeftHandMesh->SetupAttachment(LeftController);
	LeftHandMesh->SetRelativeRotation(FRotator(0, -180, 90));

	// 카메라 컴포넌트
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void APilot::BeginPlay()
{
	Super::BeginPlay();

	// VR 트래킹 및 IMC 매핑
	ModifyMapping(true);

}



// Called every frame
void APilot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Player 이동================================
	PilotDirection.Normalize();

	FTransform ControllerTransform = FTransform(this->GetControlRotation());

	FVector dir = ControllerTransform.TransformVector(PilotDirection);

	this->AddMovementInput(dir * 0.5f);

	PilotDirection = FVector::ZeroVector;
	// Player 이동================================

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

	// 라인트레이스로 버튼 클릭

}

void APilot::Pilot_TakeHeli(const FInputActionValue& value)
{
	bool TakeHeil = value.Get<bool>();

	// 어떤 액터나 컴포넌트 클래스의 이름을 정의합니다.
	TSubclassOf<AHelicopterBase> ClassFilter;

	// 오버랩된 액터의 목록을 저장할 배열을 만듭니다.
	TArray<AActor*> OverlappingActors;

	// 현재 액터의 컴포넌트에서 오버랩된 액터를 가져옵니다.
	GetOverlappingActors(OverlappingActors, ClassFilter);

	// 오버랩된 액터를 순회하면서 헬리콥터를 찾습니다.
	for (AActor* OverlappingActor : OverlappingActors) {
		AHelicopterBase* Helicopter = Cast<AHelicopterBase>(OverlappingActor);
		if (Helicopter) {
			// 헬리콥터를 찾았으므로 플레이어 캐릭터를 헬리콥터로 조종합니다.
			APlayerController* PlayerController = Cast<APlayerController>(GetController());
			if (PlayerController) {
				PlayerController->Possess(Helicopter);
			}
			break; // 헬리콥터를 찾았으므로 더 이상 반복할 필요가 없습니다.
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
