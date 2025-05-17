// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbilitySystem/BaseAttributeSet.h"

UBaseAttributeSet::UBaseAttributeSet()
{
}

void UBaseAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);


	
}

void UBaseAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
}
