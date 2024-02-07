// Fill out your copyright notice in the Description page of Project Settings.


#include "../Wheel/FrontWheel_Apache.h"

UFrontWheel_Apache::UFrontWheel_Apache()
{

	AxleType = EAxleType::Front;

	WheelRadius = 30.f;

	bAffectedByHandbrake = true;

	bABSEnabled = true;

}
