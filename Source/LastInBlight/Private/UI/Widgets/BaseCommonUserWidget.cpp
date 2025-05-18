// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/BaseCommonUserWidget.h"

void UBaseCommonUserWidget::SetWidgetController(UObject* InWidgetController)
{
	
	WidgetController=InWidgetController;
	WidgetControllerSet();
	
}
