// Fill out your copyright notice in the Description page of Project Settings.


#include "../Widget/GameEndWidget.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include "../GameModeBase/SkywardGameModeBase.h"
#include "../Helicopter/Helicopter_Apache.h"
#include <../../../../../../../Source/Runtime/UMG/Public/Components/WidgetSwitcher.h>

void UGameEndWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Apache = Cast<AHelicopter_Apache>(GetOwningPlayerPawn());

	SkywardGM = Cast<ASkywardGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

}

void UGameEndWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (SkywardGM->bIsSuccess) {
		WidgetSwitcher->SetActiveWidgetIndex(0);

	}
	else {

		WidgetSwitcher->SetActiveWidgetIndex(1);
	}

}
