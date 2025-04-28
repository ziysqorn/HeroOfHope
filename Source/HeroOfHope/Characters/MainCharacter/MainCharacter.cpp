// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include "../../Controllers/MainController/MainController.h"
#include "../../UI/GameplayProgressBar.h"

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

void AMainCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}

float AMainCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	return 0.0f;
}

void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EIComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		if (AMainController* MainController = Cast<AMainController>(GetController())) {
			EIComponent->BindAction(IA_Move, ETriggerEvent::Triggered, this, &AMainCharacter::Move);
			EIComponent->BindAction(IA_Move, ETriggerEvent::Completed, this, &AMainCharacter::StopMoving);
			EIComponent->BindAction(IA_SwitchCombatMode, ETriggerEvent::Triggered, this, &AMainCharacter::SwitchAttackMode);
		}
	}

	if (characterASComp) {
		if (InputComponent) {
			const FGameplayAbilityInputBinds Binds(
				"Confirm",
				"Cancel",
				"EPlayerAbilityInputID",
				static_cast<int32>(EPlayerAbilityInputID::Confirm),
				static_cast<int32>(EPlayerAbilityInputID::Cancel)
			);
			characterASComp->BindAbilityActivationToInputComponent(InputComponent, Binds);
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
	if (characterASComp) {
		FGameplayTag attackTag = FGameplayTag::RequestGameplayTag(FName("State.Attack"));
		FGameplayTagContainer TagContainer = characterASComp->GetOwnedGameplayTags();
		if (!TagContainer.HasTag(attackTag)) {
			FGameplayTag gameplayTag = FGameplayTag::RequestGameplayTag(FName("State.Move"));
			characterASComp->AddLooseGameplayTag(gameplayTag);
			const float DirectionValue = value.Get<float>();
			AddMovementInput(FVector(1, 0, 0), DirectionValue);
			if (DirectionValue > 0) {
				GetController()->SetControlRotation(FRotator(0, 0, 0));
			}
			else {
				GetController()->SetControlRotation(FRotator(0, 180, 0));
			}
		}
	}
}

void AMainCharacter::StopMoving()
{
	if (characterASComp) {
		FGameplayTag gameplayTag = FGameplayTag::RequestGameplayTag(FName("State.Move"));
		characterASComp->RemoveLooseGameplayTag(gameplayTag);
	}

	if (this->GetCharacterMovement()->GravityScale < 1) {
		this->GetCharacterMovement()->GravityScale = 1;
	}
}


void AMainCharacter::CustomJump()
{
	this->Jump();
}

void AMainCharacter::Landed(const FHitResult& Hit)
{
	GetCharacterMovement()->GravityScale = 1;
	attackCounter = 0;
}

void AMainCharacter::OnJumped_Implementation()
{
	if (attackCounter > 0) {
		attackCounter = 0;
	}
}

