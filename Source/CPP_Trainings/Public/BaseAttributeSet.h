// Fill out your copyright notice in the Description page of Project Settings.
// ReSharper disable CppEnforceOverridingFunctionStyle
#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "BaseAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FAttributeChangedEvent, UAttributeSet*, AttributeSet, float, OldValue, float, NewValue);

/**
 * 
 */
UCLASS()
class CPP_TRAININGS_API UBaseAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:

	UBaseAttributeSet();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated)
	FGameplayAttributeData Health;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated)
	FGameplayAttributeData MaxHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated)
	FGameplayAttributeData Mana;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated)
	FGameplayAttributeData MaxMana;

	UPROPERTY(BlueprintAssignable)
	FAttributeChangedEvent OnHealthChanged;
	
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, Health);
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, MaxHealth);
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, Mana)
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, MaxMana);
	
};
