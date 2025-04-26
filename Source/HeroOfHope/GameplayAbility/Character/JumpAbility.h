// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterAbility.h"
#include "JumpAbility.generated.h"

/**
 * 
 */
UCLASS()
class HEROOFHOPE_API UJumpAbility : public UCharacterAbility
{
	GENERATED_BODY()
	
protected:
	void ActivateAbility(
		const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData
	) override;
};
