// Fill out your copyright notice in the Description page of Project Settings.


#include "../AIController/MyAIController.h"


AMyAIController::AMyAIController()
{
    // �����ڿ��� ������ ������ �ִٸ� ���⿡ �߰��մϴ�.
}

void AMyAIController::BeginPlay()
{
    Super::BeginPlay();

    // ������ �� AI ���� �ʱ�ȭ ���� �����մϴ�.

    // ���� ��� ��ǥ ��ġ�� ������ �� �ֽ��ϴ�.
    TargetLocation = FVector((1260.000000, -1440.000000, 0.000000));

    // �ʱ�ȭ �� �̵� ����� ȣ���� �� �ֽ��ϴ�.
    MoveToTargetLocation();
}

void AMyAIController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    // �� �����Ӹ��� ������ �۾��� �ִٸ� ���⿡ �߰��մϴ�.
}

void AMyAIController::MoveToTargetLocation()
{
    // ��ǥ ��ġ�� �̵��ϵ��� ����մϴ�.
    MoveToLocation(TargetLocation);

}

