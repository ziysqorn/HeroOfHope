// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../ProjectIncludes.h"
#include "CharacterAttrSet.generated.h"

/**
 * 
 */
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)


UCLASS()
class HEROOFHOPE_API UCharacterAttrSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData MaxHealth;

	ATTRIBUTE_ACCESSORS(UCharacterAttrSet, MaxHealth);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData Health;

	ATTRIBUTE_ACCESSORS(UCharacterAttrSet, Health);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData MaxStamina;

	ATTRIBUTE_ACCESSORS(UCharacterAttrSet, MaxStamina);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData Stamina;

	ATTRIBUTE_ACCESSORS(UCharacterAttrSet, Stamina);

	void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
};
