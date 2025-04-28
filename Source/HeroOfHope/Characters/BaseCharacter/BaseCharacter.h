// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../ProjectIncludes.h"
#include "../../ASCs/CharacterASC/CharacterASC.h"
#include "../../AttrSets/Character/CharacterAttrSet.h"
#include "../../GameplayAbility/Character/CharacterAbility.h"
#include "AbilitySystemInterface.h"
#include "BaseCharacter.generated.h"

/**
 * 
 */
UCLASS()
class HEROOFHOPE_API ABaseCharacter : public APaperZDCharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

protected:
	FName CharacterName;
	//Animation sequences
	//Attack sequence
	UPROPERTY(EditDefaultsOnly, Category = "Important | Animation Sequence")
	UPaperZDAnimSequence* AttackSequence = nullptr;
	//Hurt sequence
	UPROPERTY(EditDefaultsOnly, Category = "Important | Animation Sequence")
	UPaperZDAnimSequence* HurtSequence = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = "Important | Animation Sequence")
	UPaperZDAnimSequence* DeathSequence = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Ability System Component")
	UCharacterASComp* characterASComp = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Ability System Component")
	UCharacterAttrSet* characterAttrSet = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability System Component")
	TArray<TSubclassOf<UGameplayEffect>> PassiveGameplayEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability System Component")
	TArray<TSubclassOf<UCharacterAbility>> GameplayAbilities;




	FTimerHandle HurtHandle;
	FTimerHandle DeathHandle;
	FTimerHandle AttackHandle;
	FTimerHandle StunHandle;
	FTimerHandle HitStopHandle;
	FTimerHandle DodgeHandle;
	FTimerHandle DodgeEnableHandle;

	//Flash when damaged timeline
	FTimeline FlashTimeline;

public:
	ABaseCharacter();
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;
	virtual void PossessedBy(AController* NewController) override;
	void OnRep_PlayerState() override;
	//Event taking damage
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	//Event landed
	void Landed(const FHitResult& Hit) override;

	UFUNCTION(BlueprintCallable)
	virtual void Dead() {};

	UFUNCTION()
	float GetHealthPercent();

	void FlashWhenDamaged(float Value);

	UAbilitySystemComponent* GetAbilitySystemComponent() const override{
		return characterASComp;
	}

	void GiveAbilities();
	void InitializeAttributes();

	UFUNCTION()
	FName& GetCharacterName() {
		return CharacterName;
	}

};
