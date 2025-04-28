// Fill out your copyright notice in the Description page of Project Settings.


#include "MainController.h"
#include "../../Characters/MainCharacter/MainCharacter.h"

void AMainController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);
}

void AMainController::BeginPlay()
{
	Super::BeginPlay();

	if (mainHUDSubclass) {
		MainHUD = CreateWidget<UMainCharacterHUD>(this, mainHUDSubclass);
		if (MainHUD) {
			MainHUD->AddToViewport(0);
			MainHUD->SetHealthPercent(1.0f);
			MainHUD->SetStaminaPercent(1.0f);
		}
	}
}
