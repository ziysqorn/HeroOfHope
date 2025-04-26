// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../GameplayAbility/Character/CharacterAbility.h"
#include "AttackAbility.generated.h"

/**
 * 
 */
UCLASS()
class HEROOFHOPE_API UAttackAbility : public UCharacterAbility
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AnimSequence")
	UPaperZDAnimSequence* AnimToPlay = nullptr;

	void ActivateAbility(
		const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData
	) override;

	void OnAttackAnimEnd(bool isCompleted);
};
