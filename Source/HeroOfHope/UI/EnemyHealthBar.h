// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../ProjectIncludes.h"
#include "EnemyHealthBar.generated.h"

/**
 * 
 */
UCLASS()
class HEROOFHOPE_API UEnemyHealthBar : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UProgressBar* HealthProgressBar = nullptr;
public:
	void BindHealthPercent(UObject* inObj, const FName& funcName) {
		HealthProgressBar->PercentDelegate.BindUFunction(inObj, funcName);
	}
};
