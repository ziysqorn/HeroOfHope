// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include "../../Controllers/MainController/MainController.h"

AMainCharacter::AMainCharacter()
{
	//Components setup
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	SpringArmComp->SetupAttachment(RootComponent);
	CameraComp->AttachToComponent(SpringArmComp, FAttachmentTransformRules::KeepRelativeTransform);
	//Character movement
	/*GetCharacterMovement()->MaxWalkSpeed = MoveSpeed;*/
	GetCharacterMovement()->AirControl = 0.75;
	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;


}

AMainCharacter::~AMainCharacter()
{
}

void AMainCharacter::Dead()
{

}

void AMainCharacter::BeginPlay()
{

	Super::BeginPlay();

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Overlap);

	SetupMappingContext();
}

void AMainCharacter::Tick(float DeltaSeconds)
{
	ABaseCharacter::Tick(DeltaSeconds);
}

float AMainCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (CurrentHealth > 0) {
		int FinalDamage = (int)DamageAmount;
		CurrentHealth -= FinalDamage;
		if (CurrentHealth <= 0) {
			this->Dead();
		}
		else {
			FlashTimeline.PlayFromStart();
			if (HurtSequence) {
				//GetWorldTimerManager().SetTimer(HurtHandle, FTimerDelegate::CreateUObject(this, &AMainCharacter::SetHurtToNoneState), HurtSequence->GetTotalDuration(), false);
			}
		}
	}
	return 0.0f;
}

void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (characterASComp) {
		characterASComp->InitAbilityActorInfo(this, this);
		if (InputComponent) {
			const FGameplayAbilityInputBinds BindAttack(
				"Attack",
				"",
				"EPlayerAbilityInputID",
				static_cast<int32>(EPlayerAbilityInputID::Attack)
			);
			const FGameplayAbilityInputBinds BindJump(
				"Jump",
				"",
				"EPlayerAbilityInputID",
				static_cast<int32>(EPlayerAbilityInputID::Jump)
			);
			characterASComp->BindAbilityActivationToInputComponent(InputComponent, BindAttack);
		}
	}
	if (UEnhancedInputComponent* EIComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		if (AMainController* MainController = Cast<AMainController>(GetController())) {
			EIComponent->BindAction(IA_Move, ETriggerEvent::Triggered, this, &AMainCharacter::Move);
			EIComponent->BindAction(IA_Move, ETriggerEvent::Completed, this, &AMainCharacter::StopMoving);
			EIComponent->BindAction(IA_Dodge, ETriggerEvent::Triggered, this, &AMainCharacter::Dodge);
			EIComponent->BindAction(IA_Jump, ETriggerEvent::Triggered, this, &AMainCharacter::CustomJump);
			EIComponent->BindAction(IA_Attack, ETriggerEvent::Triggered, this, &AMainCharacter::Attack);
		}
	}
}

void AMainCharacter::SetupMappingContext()
{
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController())) {
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer())) {
			Subsystem->AddMappingContext(MainMappingContext, 0);
		}
	}
	
}

void AMainCharacter::Move(const FInputActionValue& value)
{
	const float DirectionValue = value.Get<float>();
	AddMovementInput(FVector(1, 0, 0), DirectionValue);
	if (DirectionValue > 0) {
		GetController()->SetControlRotation(FRotator(0, 0, 0));
	}
	else {
		GetController()->SetControlRotation(FRotator(0, 180, 0));
	}
}

void AMainCharacter::StopMoving()
{
	if (this->GetCharacterMovement()->GravityScale < 1) {
		this->GetCharacterMovement()->GravityScale = 1;
	}
}


void AMainCharacter::Dodge()
{
}


void AMainCharacter::CustomJump()
{
	this->JumpCurrentCount = 0;
	this->GetCharacterMovement()->AddImpulse(FVector(1000 * GetSprite()->GetForwardVector().X, 0, 600), true);
}

void AMainCharacter::Attack()
{

}

void AMainCharacter::SetDodgeToNoneState()
{
}

void AMainCharacter::EndAirAttack()
{
	if (attackCounter == 3) {
		GetCharacterMovement()->GravityScale = 1;
		AMainCharacter::EndAttack();
		AMainCharacter::EndCombo();
	}
	else {
		AMainCharacter::EndAttack();
		GetCharacterMovement()->GravityScale = 1;
	}
}

void AMainCharacter::Landed(const FHitResult& Hit)
{
}

void AMainCharacter::OnJumped_Implementation()
{
	if (attackCounter > 0) {
		AMainCharacter::EndCombo();
	}
}

