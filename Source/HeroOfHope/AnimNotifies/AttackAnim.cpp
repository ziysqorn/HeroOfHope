// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackAnim.h"
#include "../Characters/BaseCharacter/BaseCharacter.h"

void UAttackAnim::OnReceiveNotify_Implementation(UPaperZDAnimInstance* OwningInstance) const
{
	if (OwningInstance) {
		if (ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(OwningInstance->GetOwningActor())) {
			FVector tempBoxPos = BoxPosition;
			tempBoxPos.X = BaseCharacter->GetActorRotation().Yaw > 0 ? -tempBoxPos.X : tempBoxPos.X;
			FVector realWorldBoxPos = BaseCharacter->GetActorLocation() + tempBoxPos;
			TArray<FHitResult> Hits;
			FCollisionObjectQueryParams ObjectFilter;
			FCollisionQueryParams AdditionParams;
			ObjectFilter.AddObjectTypesToQuery(ECollisionChannel::ECC_Pawn);
			AdditionParams.AddIgnoredActor(BaseCharacter);
			if (GetWorld()->SweepMultiByObjectType(Hits, realWorldBoxPos, realWorldBoxPos, FQuat(0, 0, 0, 0), ObjectFilter, FCollisionShape::MakeBox(BoxSize), AdditionParams)) {
				for (const FHitResult& Result : Hits) {
					TSubclassOf<UDamageType> DamageType;
					if (Result.GetActor()) {
						if (ABaseCharacter* resultCharacter = Cast<ABaseCharacter>(Result.GetActor())) {
							if (UCharacterASComp* characterASComp = Cast<UCharacterASComp>(resultCharacter->GetAbilitySystemComponent())) {
								FGameplayEffectContextHandle EffectContext = characterASComp->MakeEffectContext();
								EffectContext.AddSourceObject(this);
								if (cameraShake) {
									UGameplayStatics::PlayWorldCameraShake(this, cameraShake, BaseCharacter->GetActorLocation(), 500, 2000);
								}
								if (poisonEffect) {
									FGameplayEffectSpecHandle poisonHandle = characterASComp->MakeOutgoingSpec(poisonEffect, 1, EffectContext);
									if (poisonHandle.IsValid()) {
										FActiveGameplayEffectHandle ActiveGameplayEffectHandle = characterASComp->ApplyGameplayEffectSpecToTarget(
											*poisonHandle.Data.Get(), characterASComp);
									}
								}
								if (damageEffect) {
									FGameplayEffectSpecHandle damageHandle = characterASComp->MakeOutgoingSpec(damageEffect, 1, EffectContext);
									if (damageHandle.IsValid()) {
										FActiveGameplayEffectHandle ActiveGameplayEffectHandle = characterASComp->ApplyGameplayEffectSpecToTarget(
											*damageHandle.Data.Get(), characterASComp);
									}
								} 
							}
						}
					}
				}
			}
		}
	}
}
