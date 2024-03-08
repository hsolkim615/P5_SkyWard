// Fill out your copyright notice in the Description page of Project Settings.


#include "../Widget/HeliInfo.h"
#include "../Helicopter/Helicopter_Apache.h"
#include <../../../../../../../Source/Runtime/UMG/Public/Components/TextBlock.h>
#include "../Component/HeliComp/HeliCompBase.h"
#include "../Component/HeliComp/HeliMoveComp.h"
#include "../Component/HeliComp/HeliAttackComp.h"
#include <../../../../../../../Source/Runtime/UMG/Public/Components/ProgressBar.h>
#include "../Component/StateComponent.h"

void UHeliInfo::NativeConstruct()
{
	Super::NativeConstruct();

	Apache = Cast<AHelicopter_Apache>(GetOwningPlayerPawn());

}

void UHeliInfo::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (!Apache) {
		return;
	}

	float CurrentHealthPoint = Apache->StateComponent->HealthPoint / Apache->StateComponent->MaxHealthPoint;
	
	// 체력 갱신
	HP_Bar->SetPercent(CurrentHealthPoint);

	if (CurrentHealthPoint < 0.2) {
		HP_Bar->SetFillColorAndOpacity(FColor::Red);
	}
	else if (CurrentHealthPoint < 0.5) {
		HP_Bar->SetFillColorAndOpacity(FColor::Yellow);

	}

	// 헬기 정보 갱신
	if (txt_RollAngle && txt_PitchAngle && txt_Altitude && txt_Bullet && txt_Missile && txt_HydraMissile)
	{
		SetRollAngle();
		SetPitchAngle();
		SetAltitude();
		SetBullet();
		SetMissile();
		SetHydraMissile();
	}


}

void UHeliInfo::SetRollAngle()
{
	if (txt_RollAngle && Apache)
	{
		txt_RollAngle->SetText(FText::AsNumber(Apache->GetActorRotation().Roll));
	}
}

void UHeliInfo::SetPitchAngle()
{
	if (txt_PitchAngle && Apache)
	{
		txt_PitchAngle->SetText(FText::AsNumber(Apache->GetActorRotation().Pitch));
	}
}

void UHeliInfo::SetAltitude()
{
	if (txt_Altitude && Apache)
	{
		txt_Altitude->SetText(FText::AsNumber(Apache->GetActorLocation().Z - Cast<UHeliMoveComp>(Apache->MoveComp)->StandHigh));
	}
}

void UHeliInfo::SetBullet()
{
	if (txt_Bullet && Apache) {
		//txt_Bullet->SetText(FText::AsNumber(Cast<UHeliAttackComp>(Apache->AttackComp)->BulletNumber));
		txt_Bullet->SetText(FText::AsNumber(Apache->BulletNumber));
	}
}

void UHeliInfo::SetMissile()
{
	if (txt_Missile && Apache) {
		//txt_Missile->SetText(FText::AsNumber(Cast<UHeliAttackComp>(Apache->AttackComp)->MissileNumber));
		txt_Missile->SetText(FText::AsNumber(Apache->MissileNumber));
	}
}

void UHeliInfo::SetHydraMissile()
{
	if (txt_HydraMissile && Apache) {
		//txt_Missile->SetText(FText::AsNumber(Cast<UHeliAttackComp>(Apache->AttackComp)->MissileNumber));
		txt_HydraMissile->SetText(FText::AsNumber(Apache->HydraMissileNumber));
	}
}
