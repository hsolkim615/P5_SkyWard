// Fill out your copyright notice in the Description page of Project Settings.


#include "../Wheel/RearWheel_Apache.h"

URearWheel_Apache::URearWheel_Apache()
{
	
	AxleType = EAxleType::Rear;

	WheelRadius = 20.f;

	bAffectedByHandbrake = true;

	bABSEnabled = true;

	bAffectedBySteering = true;

}
