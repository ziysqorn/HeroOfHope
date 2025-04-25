// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../ProjectIncludes.h"
#include "CharacterAbility.generated.h"

/**
 * 
 */
UCLASS()
class HEROOFHOPE_API UCharacterAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	UCharacterAbility();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilities")
	EPlayerAbilityInputID abilityInputID = EPlayerAbilityInputID::None;
};
