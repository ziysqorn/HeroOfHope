// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseCharacter/BaseCharacter.h"
#include "../../UI/EnemyHealthBar.h"
#include "Enemy.generated.h"

/**
 * 
 */
UCLASS()
class HEROOFHOPE_API AEnemy : public ABaseCharacter
{
	GENERATED_BODY()

public:
	AEnemy();
protected:
	FTimerHandle TurnBackHandle;

	UPROPERTY(EditDefaultsOnly, Category = "Important | Wall Detect Box")
	FVector WallDetectBox = FVector(20.0f, 0.0f, 30.0f);

	UPROPERTY(EditDefaultsOnly, Category = "EnemyHealthBar")
	UWidgetComponent* HealthBarComponent = nullptr;

	void BeginPlay() override;
	void Tick(float DeltaSeconds) override;
	bool DetectingPatrolLimit();
	void TurnBackAfterTime();
	void TurnBackImmediate();
};
