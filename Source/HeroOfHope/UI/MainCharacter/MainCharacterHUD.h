// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../ProjectIncludes.h"
#include "MainCharacterHUD.generated.h"

/**
 * 
 */
UCLASS()
class HEROOFHOPE_API UMainCharacterHUD : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	void NativeConstruct() override;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UProgressBar* HealthProgressBar = nullptr;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UProgressBar* StaminaProgressBar = nullptr;

public:
	void BindHealthPercent(UObject* inObj, const FName& funcName) {
		if(IsValid(HealthProgressBar)) HealthProgressBar->PercentDelegate.BindUFunction(inObj, funcName);
	}
	void BindStaminaPercent(UObject* inObj, const FName& funcName) {
		if(IsValid(StaminaProgressBar)) StaminaProgressBar->PercentDelegate.BindUFunction(inObj, funcName);
	}
	void SetHealthPercent(float percent) {
		if (IsValid(HealthProgressBar))  HealthProgressBar->SetPercent(percent);
	}
	void SetStaminaPercent(float percent) {
		if (IsValid(StaminaProgressBar)) StaminaProgressBar->SetPercent(percent);
	}
};
