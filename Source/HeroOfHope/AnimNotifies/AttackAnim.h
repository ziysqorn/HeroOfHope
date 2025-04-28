// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../ProjectIncludes.h"
#include "AttackAnim.generated.h"

/**
 * 
 */
UCLASS()
class HEROOFHOPE_API UAttackAnim : public UPaperZDAnimNotify
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BoxSize")
	FVector BoxSize;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BoxPosition")
	FVector BoxPosition;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GameplayEffect")
	TSubclassOf<UGameplayEffect> poisonEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GameplayEffect")
	TSubclassOf<UGameplayEffect> damageEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GameplayEffect")
	TSubclassOf<UCameraShakeBase> cameraShake;

	void OnReceiveNotify_Implementation(UPaperZDAnimInstance* OwningInstance = nullptr) const override;
};
