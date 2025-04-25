// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseCharacter/BaseCharacter.h"
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
	UInputAction* IA_Shoot = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inputs|InputAction")
	UInputAction* IA_PauseGame = nullptr;

	//Input mapping context
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inputs|InputMapping")
	UInputMappingContext* MainMappingContext = nullptr;

	//Animation Sequences
	//Sword default combo
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Sequences|Slash Default Combo")
	UPaperZDAnimSequence* Slash1 = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Sequences|Slash Default Combo")
	UPaperZDAnimSequence* Slash2 = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Sequences|Slash Default Combo")
	UPaperZDAnimSequence* Slash3 = nullptr;

	//Sword air combo
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Sequences|Air Slash Combo")
	UPaperZDAnimSequence* AirSlash1 = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Sequences|Air Slash Combo")
	UPaperZDAnimSequence* AirSlash2 = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Sequences|Air Slash Combo")
	UPaperZDAnimSequence* AirSlash3 = nullptr;
	//Bow-combat
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Sequences|Bow-combat")
	UPaperZDAnimSequence* BowShoot = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Sequences|Bow-combat")
	UPaperZDAnimSequence* JumpShoot = nullptr;

	//Timer Handle
	FTimerHandle ComboHandle;
	FTimerHandle SheatheSwordHandle;

	//Sheathe the sword
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Is the Sword Sheathed ?")
	bool isSwordSheathed = true;

	//Attack counter
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attack Counter")
	int attackCounter{0};

	//Check character is sliding on the wall
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Character hit a wall ?")
	bool WallSliding{ false };

public:
	AMainCharacter();
	~AMainCharacter();
	//Inputs settup
	void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void SetupMappingContext();

	UFUNCTION(BlueprintCallable)
	int GetATKDamage() {
		return ATK_Damage;
	}



	//Actions
	virtual void Move(const FInputActionValue& value);
	virtual void StopMoving();
	void Dodge();
	void CustomJump();
	virtual void Attack();
	void SheatheSword() {
		isSwordSheathed = true;
	}
	virtual void EndAttack() {
	}
	void EndAirAttack();

	virtual void EndCombo() {
		attackCounter = 0;
	}

	void SetDodgeToNoneState();

	void CanDodgeEnable() {
		if (!canDodge) canDodge = true;
	}

	void Dead() override;
	//Events
	//Event begin play
	void BeginPlay() override;
	//Event tick
	void Tick(float DeltaSeconds) override;

	float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	//Event landed
	void Landed(const FHitResult& Hit) override;
	//Event on jumped
	void OnJumped_Implementation() override;
};
