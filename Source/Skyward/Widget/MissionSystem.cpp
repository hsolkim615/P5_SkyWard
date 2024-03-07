// Fill out your copyright notice in the Description page of Project Settings.


#include "../Widget/MissionSystem.h"
#include <../../../../../../../Source/Runtime/UMG/Public/Components/WidgetSwitcher.h>
#include <../../../../../../../Source/Runtime/UMG/Public/Components/TextBlock.h>
#include "../Helicopter/Helicopter_Apache.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include "../GameModeBase/SkywardGameModeBase.h"


void UMissionSystem::NativeConstruct()
{
	Super::NativeConstruct();

	Apache = Cast<AHelicopter_Apache>(GetOwningPlayerPawn());

	SkywardGM = Cast<ASkywardGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

}

void UMissionSystem::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);


	SetTankNumber();

	SetBuildingNumber();



	if (SkywardGM->DestroyEnemyBuliding >= 3) {
		SwitchMission(2);
	}
	else if (SkywardGM->DestroyMoveTank >= 5) {
		SwitchMission(1);

	}

}

void UMissionSystem::SetTankNumber()
{
	if (txt_Mission_First_Tank && Apache)
	{
		txt_Mission_First_Tank->SetText(FText::AsNumber(SkywardGM->DestroyMoveTank));
	}
}

void UMissionSystem::SetBuildingNumber()
{
	if (txt_Mission_Second_Buliding && Apache)
	{
		txt_Mission_Second_Buliding->SetText(FText::AsNumber(SkywardGM->DestroyEnemyBuliding));
	}

}

void UMissionSystem::SwitchMission(int32 IndexNum)
{
	WidgetSwitcher->SetActiveWidgetIndex(IndexNum);

}
