// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"

ABaseCharacter::ABaseCharacter()
{
	characterASComp = CreateDefaultSubobject<UCharacterASComp>("AbilitySystemComponent");
	characterAttrSet = CreateDefaultSubobject<UCharacterAttrSet>("CharacterAttrSet");
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
 	/*if (FlashCurveFloat) {
		FlashTimeline.AddInterpFloat(FlashCurveFloat, FOnTimelineFloatStatic::CreateUObject(this, &ABaseCharacter::FlashWhenDamaged));
	}*/
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Ignore);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_GameTraceChannel2, ECR_Ignore);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
}


void ABaseCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	FlashTimeline.TickTimeline(DeltaSeconds);
}

void ABaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (characterASComp) {
		characterASComp->InitAbilityActorInfo(this, this);
	}

	InitializeAttributes();
	GiveAbilities();
}

void ABaseCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	if (characterASComp) {
		characterASComp->InitAbilityActorInfo(this, this);
	}

	InitializeAttributes();

	if (characterASComp) {
		if (InputComponent) {
			const FGameplayAbilityInputBinds Binds(
				"Confirm",
				"Cancel",
				"EPlayerAbilityInputID",
				static_cast<int32>(EPlayerAbilityInputID::Confirm),
				static_cast<int32>(EPlayerAbilityInputID::Cancel)
			);
			characterASComp->BindAbilityActivationToInputComponent(InputComponent, Binds);
		}
	}
}

void ABaseCharacter::Landed(const FHitResult& Hit)
{
}

void ABaseCharacter::FlashWhenDamaged(float Value)
{
	UMaterialInstanceDynamic* DynamicMaterial = this->GetSprite()->CreateDynamicMaterialInstance(0);
	DynamicMaterial->SetScalarParameterValue("FlashMultiplier", Value);
}

void ABaseCharacter::GiveAbilities()
{
	check(characterASComp);
	for (TSubclassOf<UCharacterAbility>& gameplayAbility : GameplayAbilities) {
		characterASComp->GiveAbility(FGameplayAbilitySpec(
			gameplayAbility, 1,
			static_cast<int32>(gameplayAbility.GetDefaultObject()->abilityInputID),
			this
		));
	}
}

void ABaseCharacter::InitializeAttributes()
{
	check(characterASComp); 
	for (const TSubclassOf<UGameplayEffect>& gameplayEffect : PassiveGameplayEffect) {
		FGameplayEffectContextHandle EffectContext = characterASComp->MakeEffectContext();
		EffectContext.AddSourceObject(this);

		FGameplayEffectSpecHandle NewHandle = characterASComp->MakeOutgoingSpec(gameplayEffect, 1, EffectContext);

		if (NewHandle.IsValid()) {
			FActiveGameplayEffectHandle ActiveGameplayEffectHandle = characterASComp->ApplyGameplayEffectSpecToSelf(
				*NewHandle.Data.Get());
		}
	}
}


float ABaseCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (CurrentHealth > 0) {
		int FinalDamage = (int)DamageAmount;
		CurrentHealth -= FinalDamage;
		if (CurrentHealth <= 0) {
			this->Dead();
		}
		else {
			FlashTimeline.PlayFromStart();
			if (HurtSequence) {
				/*GetWorldTimerManager().SetTimer(HurtHandle, FTimerDelegate::CreateUObject(this, &ABaseCharacter::SetHurtToNoneState), 
					HurtSequence->GetTotalDuration(), false);*/
			}
		}
	}
	return 0.0f;
}
