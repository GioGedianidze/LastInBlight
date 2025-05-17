// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "BaseAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)
 

/**
 * 
 */
UCLASS()
class LASTINBLIGHT_API UBaseAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:

	UBaseAttributeSet();

	//Vital
	UPROPERTY(BlueprintReadOnly,Category="Attribute|Vital")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, Health);

	UPROPERTY(BlueprintReadOnly,Category="Attribute|Vital")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, Mana);

	//Primary
	
	UPROPERTY(BlueprintReadOnly,Category="Attribute|Secondary")
	FGameplayAttributeData Intelligence;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, Intelligence);
	
	//Secondary
	UPROPERTY(BlueprintReadOnly,Category="Attribute|Secondary")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, MaxHealth);

	UPROPERTY(BlueprintReadOnly,Category="Attribute|Secondary")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, MaxMana);


protected:

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	
	
	
};
