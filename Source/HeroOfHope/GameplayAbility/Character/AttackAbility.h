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
	UPaperZDAnimSequence* Slash1 = nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AnimSequence")
	UPaperZDAnimSequence* Slash2 = nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AnimSequence")
	UPaperZDAnimSequence* Slash3 = nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AnimSequence")
	UPaperZDAnimSequence* AirSlash1 = nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AnimSequence")
	UPaperZDAnimSequence* AirSlash2 = nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AnimSequence")
	UPaperZDAnimSequence* AirSlash3 = nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AnimSequence")
	UPaperZDAnimSequence* Punch1 = nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AnimSequence")
	UPaperZDAnimSequence* Punch2 = nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AnimSequence")
	UPaperZDAnimSequence* Punch3 = nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AnimSequence")
	UPaperZDAnimSequence* Kick1 = nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AnimSequence")
	UPaperZDAnimSequence* Kick2 = nullptr;

	void ActivateAbility(
		const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData
	) override;

	FTimerHandle AttackHandle;
};
