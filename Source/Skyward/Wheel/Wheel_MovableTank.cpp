// Fill out your copyright notice in the Description page of Project Settings.


#include "../Wheel/Wheel_MovableTank.h"


UWheel_MovableTank::UWheel_MovableTank() 
{
	WheelRadius = 45.f;

	bAffectedByBrake = true;

	bAffectedByHandbrake = true;

	bAffectedByEngine = true;

	bABSEnabled = true;


}
