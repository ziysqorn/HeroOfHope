// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacterHUD.h"
#include "../../Controllers/MainController/MainController.h"
#include "../../Characters/MainCharacter/MainCharacter.h"

void UMainCharacterHUD::NativeConstruct()
{
	Super::NativeConstruct();

	if (AMainController* MainController = Cast<AMainController>(this->GetOwningPlayer())) {
		if (AMainCharacter* MainCharacter = Cast<AMainCharacter>(MainController->GetPawn())) {
			HealthProgressBar->PercentDelegate.BindUFunction(MainCharacter, FName("GetHealthPercent"));
			StaminaProgressBar->PercentDelegate.BindUFunction(MainCharacter, FName("GetStaminaPercent"));
		}
	}
}
