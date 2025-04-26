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
	//Character's base stats
	int MaxHealth;
	int ATK_Damage;
	//Character's gameplay temporary stats
	int CurrentHealth = MaxHealth;
	//Can character dodge ?
	bool canDodge = true;
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
	void PossessedBy(AController* NewController) override;
	void OnRep_PlayerState() override;
	//Event taking damage
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	//Event landed
	void Landed(const FHitResult& Hit) override;

	UFUNCTION(BlueprintCallable)
	virtual void Dead() {};

	void FlashWhenDamaged(float Value);

	int GetMaxHealth() {
		return MaxHealth;
	}
	int GetCurrentHealth() {
		return CurrentHealth;
	}

	UAbilitySystemComponent* GetAbilitySystemComponent() const override{
		return characterASComp;
	}

	void GiveAbilities();
	void InitializeAttributes();

	UFUNCTION()
	float GetHealthPercentage() const {
		return (float)CurrentHealth / MaxHealth;
	}

	UFUNCTION()
	FName& GetCharacterName() {
		return CharacterName;
	}

	FTimerHandle& GetHitStopHandle() { 
		return HitStopHandle; 
	}


	//Set Damage (min = 1) by a buff (pass in negative value = debuff)
	void SetATKDamageByBuff(const int& Buff) {
		if ((Buff < 0 && abs(Buff) < ATK_Damage) || Buff >= 0) {
			ATK_Damage += Buff;
		}
		else {
			ATK_Damage = 1;
		}
	}
	//Set Damage (min = 0) directly by a new value
	void SetATKDamageByNewValue(const int& NewDamage) {
		if (NewDamage >= 0) {
			ATK_Damage = NewDamage;
		}
		else {
			ATK_Damage = 0;
		}
	}
	//Set max health (min = 1) by a buff (pass in negative value = debuff)
	void SetMaxHealthByBuff(const int& Buff) {
		if ((Buff < 0 && abs(Buff) < MaxHealth) || Buff >= 0) {
			MaxHealth += Buff;
		}
		else {
			MaxHealth = 1;
		}
	}
	void SetCurrentHealthByBuff(const int& Buff) {
		int finalHealth = CurrentHealth + Buff;
		if (finalHealth > MaxHealth) CurrentHealth = MaxHealth;
		else if (finalHealth < 0) CurrentHealth = 0;
		else CurrentHealth = finalHealth;
	}
	//Set max health (min=0) directly by a new value
	void SetMaxHealthByNewValue(const int& NewMaxHealth) {
		if (NewMaxHealth >= 0) {
			MaxHealth = NewMaxHealth;
		}
		else {
			MaxHealth = 0;
		}
	}
	
	//Return character damage amount after a buff (or debuff)
	virtual int CalculatedDamage(const int& Buff) {
		if ((Buff < 0 && abs(Buff) < ATK_Damage) || Buff >= 0) {
			return ATK_Damage + Buff;
		}
		return 0;
	}
};
