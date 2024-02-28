// Fill out your copyright notice in the Description page of Project Settings.


#include "../Component/StateComponent.h"

// Sets default values for this component's properties
UStateComponent::UStateComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	StateComponent = this;

	// ...
}


// Called when the game starts
void UStateComponent::BeginPlay()
{
	Super::BeginPlay();

	SetHealthPoint(MaxHealthPoint);

}


// Called every frame
void UStateComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UStateComponent::SetMaxHealthPoint(float NewMaxHealthPoint)
{
	// 최대 체력 설정
	
	MaxHealthPoint = NewMaxHealthPoint;

}

void UStateComponent::SetHealthPoint(float NewHealthPoint)
{
	// 체력 설정
	
	HealthPoint = NewHealthPoint;
}

void UStateComponent::SetAttackDamage(float NewAttackDamage)
{
	// 데미지 설정
	
	AttackDamage = NewAttackDamage;

}

void UStateComponent::TakeDamage(float Damage)
{
	// 피격기능 

	HealthPoint -= Damage;

	if (HealthPoint < 0) {
		HealthPoint = 0;

		StateDestroy();

	}

}

void UStateComponent::StateDestroy()
{
	// 적합한 효과 등 연출하거나 등등


}

UStateComponent* UStateComponent::GetStateComponent()
{
	return StateComponent;
}

