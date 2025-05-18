// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BaseHUD.h"
#include "CommonUserWidget.h"
#include "UI/Widgets/BaseCommonUserWidget.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/UserWidget.h"
#include "UI/WidgetControllers/OverlayWidgetController.h"

UOverlayWidgetController* ABaseHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	if (OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this,OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WCParams);
		OverlayWidgetController->BindCallbacksToDependencies();

		return OverlayWidgetController;
	}
	return OverlayWidgetController;
}

void ABaseHUD::InitOverlay(APlayerController* PC, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{

	checkf(OverlayWidgetClass, TEXT("Overlay Widget class is not initialized"));
	checkf(OverlayWidgetControllerClass,TEXT("Overlay Widget contyroller class is not initialized"));
	
	UCommonUserWidget* Widget = CreateWidget<UCommonUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget = Cast<UBaseCommonUserWidget>(Widget);
	
	const FWidgetControllerParams WidgetControllerParams(PC,ASC,AS);
	UOverlayWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams);
	
	OverlayWidget->SetWidgetController(WidgetController);
	WidgetController->BroadcastInitialValues();
	
	Widget->AddToViewport();
	
}

