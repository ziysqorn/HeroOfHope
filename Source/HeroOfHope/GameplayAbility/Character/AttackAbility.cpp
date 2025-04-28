// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackAbility.h"
#include "../../Characters/MainCharacter/MainCharacter.h"

void UAttackAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{ 
	if (AMainCharacter* MainCharacter = Cast<AMainCharacter>(ActorInfo->OwnerActor)) {
		++MainCharacter->attackCounter;
		if (MainCharacter->isUsingSword) {
			switch (MainCharacter->attackCounter) {
			case 1:
				if (MainCharacter->GetVelocity().Z == 0.0f) {
					if (Slash1) {
						GetWorld()->GetTimerManager().SetTimer(AttackHandle,
							FTimerDelegate::CreateUObject(this, &UAttackAbility::EndAbility, Handle, ActorInfo, ActivationInfo, false, false),
							Slash1->GetTotalDuration(), false);
						MainCharacter->EndComboTimer(Slash1->GetTotalDuration() + 1.0f);
					}
				}
				else {
					if (AirSlash1) {
						GetWorld()->GetTimerManager().SetTimer(AttackHandle,
							FTimerDelegate::CreateUObject(this, &UAttackAbility::EndAbility, Handle, ActorInfo, ActivationInfo, false, false),
							AirSlash1->GetTotalDuration(), false);
						MainCharacter->EndComboTimer(AirSlash1->GetTotalDuration() + 1.0f);
						MainCharacter->GetCharacterMovement()->GravityScale = 0.5f;
					}
				}
				break;
			case 2:
				if (MainCharacter->GetVelocity().Z == 0.0f) {
					if (Slash2) {
						GetWorld()->GetTimerManager().SetTimer(AttackHandle,
							FTimerDelegate::CreateUObject(this, &UAttackAbility::EndAbility, Handle, ActorInfo, ActivationInfo, false, false),
							Slash2->GetTotalDuration(), false);
						MainCharacter->EndComboTimer(Slash2->GetTotalDuration() + 1.0f);
					}
				}
				else {
					if (AirSlash2) {
						GetWorld()->GetTimerManager().SetTimer(AttackHandle,
							FTimerDelegate::CreateUObject(this, &UAttackAbility::EndAbility, Handle, ActorInfo, ActivationInfo, false, false),
							AirSlash2->GetTotalDuration(), false);
						MainCharacter->EndComboTimer(AirSlash2->GetTotalDuration() + 1.0f);
						MainCharacter->GetCharacterMovement()->GravityScale = 0.5f;
					}
					MainCharacter->attackCounter = 0;
				}
				break;
			case 3:
				if (MainCharacter->GetVelocity().Z == 0.0f) {
					if (Slash3) {
						GetWorld()->GetTimerManager().SetTimer(AttackHandle,
							FTimerDelegate::CreateUObject(this, &UAttackAbility::EndAbility, Handle, ActorInfo, ActivationInfo, false, false),
							Slash3->GetTotalDuration(), false);
						MainCharacter->EndComboTimer(Slash3->GetTotalDuration() + 1.0f);
					}
					MainCharacter->attackCounter = 0;
				}
				break;
			}
		}
		else {
			switch (MainCharacter->attackCounter) {
			case 1:
				if (Punch1) {
					GetWorld()->GetTimerManager().SetTimer(AttackHandle,
						FTimerDelegate::CreateUObject(this, &UAttackAbility::EndAbility, Handle, ActorInfo, ActivationInfo, false, false),
						Punch1->GetTotalDuration(), false);
					MainCharacter->EndComboTimer(Punch1->GetTotalDuration() + 1.0f);
				}
				break;
			case 2:
				if (Punch2) {
					GetWorld()->GetTimerManager().SetTimer(AttackHandle,
						FTimerDelegate::CreateUObject(this, &UAttackAbility::EndAbility, Handle, ActorInfo, ActivationInfo, false, false),
						Punch2->GetTotalDuration(), false);
					MainCharacter->EndComboTimer(Punch2->GetTotalDuration() + 1.0f);
				}
				break;
			case 3:
				if (Punch3) {
					GetWorld()->GetTimerManager().SetTimer(AttackHandle,
						FTimerDelegate::CreateUObject(this, &UAttackAbility::EndAbility, Handle, ActorInfo, ActivationInfo, false, false),
						Punch3->GetTotalDuration(), false);
					MainCharacter->EndComboTimer(Punch3->GetTotalDuration() + 1.0f);
				}
				break;
			case 4:
				if (Kick1) {
					GetWorld()->GetTimerManager().SetTimer(AttackHandle,
						FTimerDelegate::CreateUObject(this, &UAttackAbility::EndAbility, Handle, ActorInfo, ActivationInfo, false, false),
						Kick1->GetTotalDuration(), false);
					MainCharacter->EndComboTimer(Kick1->GetTotalDuration() + 1.0f);
				}
				break;
			case 5:
				if (Kick2) {
					GetWorld()->GetTimerManager().SetTimer(AttackHandle,
						FTimerDelegate::CreateUObject(this, &UAttackAbility::EndAbility, Handle, ActorInfo, ActivationInfo, false, false),
						Kick2->GetTotalDuration(), false);
					MainCharacter->EndComboTimer(Kick2->GetTotalDuration() + 1.0f);
				}
				MainCharacter->attackCounter = 0;
				break;
			}
		}
	}
}
