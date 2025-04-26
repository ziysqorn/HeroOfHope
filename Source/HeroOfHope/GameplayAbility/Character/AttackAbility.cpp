// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackAbility.h"
#include "../../Characters/BaseCharacter/BaseCharacter.h"

void UAttackAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(ActorInfo->OwnerActor)) {
		if (AnimToPlay) {
			FZDOnAnimationOverrideEndSignature AnimationEndSignature;
			AnimationEndSignature.BindUObject(this, &UAttackAbility::OnAttackAnimEnd);
			if(BaseCharacter->GetAnimInstance()) 
				BaseCharacter->GetAnimInstance()->PlayAnimationOverride(AnimToPlay);
		}
	}
}

void UAttackAbility::OnAttackAnimEnd(bool isCompleted)
{
	EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), false, false);
}
