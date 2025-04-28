// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterAttrSet.h"
#include "../../Characters/BaseCharacter/BaseCharacter.h"
#include "../../Controllers/MainController/MainController.h"

void UCharacterAttrSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetHealthAttribute()) {
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
	}
	if (Attribute == GetStaminaAttribute()) {
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxStamina());
	}
}

void UCharacterAttrSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	if (Data.EvaluatedData.Attribute == GetHealthAttribute()) {
		const float localHealth = GetHealth();
		if (localHealth <= 0.0f) {
			if (Data.Target.GetOwnerActor()) {
				Data.Target.GetOwnerActor()->Destroy();
			}
		}
	}
}
