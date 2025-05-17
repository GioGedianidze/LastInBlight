// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "Interaction/EnemyInterface.h"
#include "BaseEnemyClass.generated.h"

/**
 * 
 */
UCLASS()
class LASTINBLIGHT_API ABaseEnemyClass : public ABaseCharacter, public IEnemyInterface
{
	GENERATED_BODY()
public:

	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;

	ABaseEnemyClass();
protected:
	
	

	
	UPROPERTY(EditAnywhere, Category="Weapon")
	TObjectPtr<USkeletalMeshComponent> WeaponR;

	UPROPERTY(EditAnywhere, Category="Weapon")
	TObjectPtr<USkeletalMeshComponent> WeaponL;
	
	
	
};
