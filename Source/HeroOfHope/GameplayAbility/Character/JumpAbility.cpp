// Fill out your copyright notice in the Description page of Project Settings.


#include "JumpAbility.h"
#include "../../Characters/MainCharacter/MainCharacter.h"

void UJumpAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (ActorInfo) {
		if (AMainCharacter* MainCharacter = Cast<AMainCharacter>(ActorInfo->OwnerActor)) {
			MainCharacter->CustomJump();
		}
	}
	EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
}
