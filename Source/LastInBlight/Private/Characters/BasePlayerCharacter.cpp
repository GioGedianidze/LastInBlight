// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BasePlayerCharacter.h"

#include "Controllers/BasePlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UI/BaseHUD.h"

ABasePlayerCharacter::ABasePlayerCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f,400.f,0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;


	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
}

void ABasePlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	InitAbilityActorInfo();
}


void ABasePlayerCharacter::InitAbilityActorInfo()
{
	
	
	if(ABasePlayerController* BasePlayerController =  Cast<ABasePlayerController> (GetController()))
	{
		if(ABaseHUD* BaseHUD =  Cast<ABaseHUD>(BasePlayerController->GetHUD()))
		{
			BaseHUD->InitOverlay(BasePlayerController,AbilitySystemComponent,AttributeSet);
		}
	}
}
