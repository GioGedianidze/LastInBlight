// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetControllers/BaseWidgetController.h"

void UBaseWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WCParams)
{
	PlayerController = WCParams.PlayerController;
	AbilitySystemComponent = WCParams.AbilitySystemComponent;
	AttributeSet = WCParams.AttributeSet;
}

void UBaseWidgetController::BroadcastInitialValues()
{
	
}

void UBaseWidgetController::BindCallbacksToDependencies()
{
}
