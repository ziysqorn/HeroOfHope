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

	if (characterASComp) {
		characterASComp->InitAbilityActorInfo(this, this);
	}
}


void ABaseCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	FlashTimeline.TickTimeline(DeltaSeconds);
}

void ABaseCharacter::Landed(const FHitResult& Hit)
{
}

void ABaseCharacter::FlashWhenDamaged(float Value)
{
	UMaterialInstanceDynamic* DynamicMaterial = this->GetSprite()->CreateDynamicMaterialInstance(0);
	DynamicMaterial->SetScalarParameterValue("FlashMultiplier", Value);
}

void ABaseCharacter::AddStartupGameplayAbilities()
{
	check(characterASComp);
	for (TSubclassOf<UCharacterAbility>& gameplayAbility : GameplayAbilities) {
		characterASComp->GiveAbility(FGameplayAbilitySpec(
			gameplayAbility, 1,
			static_cast<int32>(gameplayAbility.GetDefaultObject()->abilityInputID),
			this
		));
	}

	for (const TSubclassOf<UGameplayEffect>& gameplayEffect : PassiveGameplayEffect) {
		FGameplayEffectContextHandle EffectContext = characterASComp->MakeEffectContext();
		EffectContext.AddSourceObject(this);

		FGameplayEffectSpecHandle NewHandle = characterASComp->MakeOutgoingSpec(gameplayEffect, 1, EffectContext);

		if (NewHandle.IsValid()) {
			FActiveGameplayEffectHandle ActiveGameplayEffectHandle = characterASComp->ApplyGameplayEffectSpecToTarget(
				*NewHandle.Data.Get(), characterASComp);

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
		/*if (StatsPopoutSubclass) {
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			if (AStatsPopout* stats = GetWorld()->SpawnActor<AStatsPopout>(StatsPopoutSubclass, this->GetActorLocation(), FRotator(0.0f, 0.0f, 0.0f), SpawnParams)) {
				if (UStatsPopoutUI* statsUI = stats->GetStatsPopoutUI()) {
					FText inText = FText::FromString(FString::FromInt(FinalDamage));
					statsUI->SetText(inText);
				}
			}
		}*/
	}
	return 0.0f;
}
