// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "BasePlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class LASTINBLIGHT_API ABasePlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()


public:
	ABasePlayerCharacter();
	
	virtual void PossessedBy(AController* NewController) override;

private:
	virtual void InitAbilityActorInfo();
};
