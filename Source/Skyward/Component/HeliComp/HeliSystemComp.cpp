// Fill out your copyright notice in the Description page of Project Settings.


#include "../../Component/HeliComp/HeliSystemComp.h"
#include <../../../../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h>
#include "../../Helicopter/Helicopter_Apache.h"
#include <../../../../../../../Source/Runtime/UMG/Public/Components/WidgetComponent.h>
#include "../../GameModeBase/SkywardGameModeBase.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h>

UHeliSystemComp::UHeliSystemComp()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UHeliSystemComp::BeginPlay()
{
	Super::BeginPlay();

	SkywardGM = Cast<ASkywardGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

}

void UHeliSystemComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (SkywardGM->bIsSuccess == true) {
	
		Apache->HeliInfoUIComp->SetVisibility(false);
		Apache->MissionUIComp->SetVisibility(false);

		Apache->GameEndUI1->SetVisibility(true);
		Apache->GameEndUI2->SetVisibility(true);
		Apache->GameEndUI3->SetVisibility(true);
		Apache->GameEndUI4->SetVisibility(true);

	}

}

void UHeliSystemComp::SetupPlayerInput(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInput(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	// VR 컨트롤러 바인딩
	if (EnhancedInputComponent) {

		// 헬기 엔진
		EnhancedInputComponent->BindAction(IA_Apache_Menu, ETriggerEvent::Started, this, &UHeliSystemComp::MissionWidget);

	}
}

void UHeliSystemComp::MissionWidget()
{
	Apache->MissionUIComp->SetVisibility(!Apache->MissionUIComp->IsVisible());
}
