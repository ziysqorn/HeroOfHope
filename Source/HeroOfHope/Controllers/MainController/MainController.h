// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../ProjectIncludes.h"
#include "../../UI/MainCharacter/MainCharacterHUD.h"
#include "MainController.generated.h"

/**
 * 
 */
UCLASS()
class HEROOFHOPE_API AMainController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	UPROPERTY()
	UMainCharacterHUD* MainHUD = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "HUD")
	TSubclassOf<UMainCharacterHUD> mainHUDSubclass;
public:
	void OnPossess(APawn* aPawn) override;
	void BeginPlay() override;
};
