// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbilitySystem/BaseAttributeSet.h"

UBaseAttributeSet::UBaseAttributeSet()
{
	InitHealth(15.f);
	InitMaxHealth(100.f);

	InitMana(25.f);
	InitMaxMana(100.f);
}

void UBaseAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);


	
}

void UBaseAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
}
