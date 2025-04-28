// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../ProjectIncludes.h"
#include "GameplayProgressBar.generated.h"

/**
 * 
 */
UCLASS()
class HEROOFHOPE_API UGameplayProgressBar : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UProgressBar* GameplayProgressBar = nullptr;
public:
	void BindPercent(UObject* inObj, const FName& funcName) {
		GameplayProgressBar->PercentDelegate.BindUFunction(inObj, funcName);
	}
};
