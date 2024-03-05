// Fill out your copyright notice in the Description page of Project Settings.


#include "../../Component/HeliComp/HeliSystemComp.h"
#include <../../../../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h>
#include "../../Helicopter/Helicopter_Apache.h"
#include <../../../../../../../Source/Runtime/UMG/Public/Components/WidgetComponent.h>

UHeliSystemComp::UHeliSystemComp()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UHeliSystemComp::BeginPlay()
{
	Super::BeginPlay();

}

void UHeliSystemComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

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
