// Fill out your copyright notice in the Description page of Project Settings.


#include "../AIController/MyAIController.h"


AMyAIController::AMyAIController()
{
    // 생성자에서 설정할 내용이 있다면 여기에 추가합니다.
}

void AMyAIController::BeginPlay()
{
    Super::BeginPlay();

    // 시작할 때 AI 동작 초기화 등을 수행합니다.

    // 예를 들어 목표 위치를 설정할 수 있습니다.
    TargetLocation = FVector((1260.000000, -1440.000000, 0.000000));

    // 초기화 후 이동 명령을 호출할 수 있습니다.
    MoveToTargetLocation();
}

void AMyAIController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    // 매 프레임마다 수행할 작업이 있다면 여기에 추가합니다.
}

void AMyAIController::MoveToTargetLocation()
{
    // 목표 위치로 이동하도록 명령합니다.
    MoveToLocation(TargetLocation);

}

