// Fill out your copyright notice in the Description page of Project Settings.


#include "../GameModeBase/SkywardGameModeBase.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h>

ASkywardGameModeBase::ASkywardGameModeBase()
{
    PrimaryActorTick.bCanEverTick =true;

}

void ASkywardGameModeBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);


    if (bIsSuccess && !bIsTimerSet)
    {

        GetWorldTimerManager().SetTimer(GameTimerHandle, this, &ASkywardGameModeBase::ChangeLevel, 10.0f, false);

        // Ÿ�̸� ���� �� �÷��� �ʱ�ȭ
        
        bIsTimerSet = true;
    }
    else if (bIsFail && !bIsTimerSet) {
        GetWorldTimerManager().SetTimer(GameTimerHandle, this, &ASkywardGameModeBase::ChangeLevel, 10.0f, false);

        // Ÿ�̸� ���� �� �÷��� �ʱ�ȭ
        
        bIsTimerSet = true;

    }

}

void ASkywardGameModeBase::ChangeLevel()
{
    bIsTimerSet = false;

    UGameplayStatics::OpenLevel(GetWorld(), FName(TEXT("L_LogIn")));
   
    UE_LOG(LogTemp, Warning, TEXT("Success"));

    bIsSuccess = false;
    bIsFail = false;


}
