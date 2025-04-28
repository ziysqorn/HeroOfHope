// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseCharacter/BaseCharacter.h"
#include "../../UI/MainCharacter/MainCharacterHUD.h"
#include "MainCharacter.generated.h"

/**
 * 
 */

UCLASS() 
class HEROOFHOPE_API AMainCharacter : public ABaseCharacter
{
	GENERATED_BODY()
protected:
	//Spring Arm and Camera Components
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spring Arm")
	USpringArmComponent* SpringArmComp = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	UCameraComponent* CameraComp = nullptr;

	//Input Action 
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inputs|InputAction")
	UInputAction* IA_Move = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inputs|InputAction")
	UInputAction* IA_Dodge = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inputs|InputAction")
	UInputAction* IA_Jump = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inputs|InputAction")
	UInputAction* IA_Attack = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inputs|InputAction")
	UInputAction* IA_SwitchCombatMode = nullptr;

	//Input mapping context
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inputs|InputMapping")
	UInputMappingContext* MainMappingContext = nullptr;

	//Timer Handle
	FTimerHandle ComboHandle;

public:
	//Attack counter
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attack Counter")
	int attackCounter = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AttackMode")
	bool isUsingSword = true;

public:
	AMainCharacter();
	~AMainCharacter();
	//Inputs settup
	void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void SetupMappingContext();


	UFUNCTION()
	float GetStaminaPercent() {
		return 0.0f;
	}


	//Actions
	virtual void Move(const FInputActionValue& value);
	virtual void StopMoving();
	void SwitchAttackMode() {
		isUsingSword = !isUsingSword;
		attackCounter = 0;
	}
	void CustomJump();

	void EndComboTimer(float delay) {
		GetWorldTimerManager().SetTimer(ComboHandle, FTimerDelegate::CreateUObject(this, &AMainCharacter::EndCombo), delay, false);
	}

	void EndCombo() {
		attackCounter = 0;
		GetCharacterMovement()->GravityScale = 1.0f;
	}

	void Dead() override;
	//Events
	//Event begin play
	void BeginPlay() override;
	//Event tick
	void Tick(float DeltaSeconds) override;

	void PossessedBy(AController* NewController) override;

	float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	//Event landed
	void Landed(const FHitResult& Hit) override;
	//Event on jumped
	void OnJumped_Implementation() override;
};
