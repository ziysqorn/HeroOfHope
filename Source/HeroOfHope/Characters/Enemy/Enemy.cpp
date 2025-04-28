// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"

AEnemy::AEnemy()
{
	HealthBarComponent = CreateDefaultSubobject<UWidgetComponent>("HealthBarComponent");
	HealthBarComponent->SetupAttachment(RootComponent);
	HealthBarComponent->SetWidgetSpace(EWidgetSpace::Screen);
	HealthBarComponent->SetDrawAtDesiredSize(false);
}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	if (UEnemyHealthBar* healthBar = Cast<UEnemyHealthBar>(HealthBarComponent->GetUserWidgetObject())) {
		healthBar->BindHealthPercent(this, FName("GetHealthPercent"));
	}
}

void AEnemy::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!DetectingPatrolLimit()) {
		if (ACharacter* MainCharacter = UGameplayStatics::GetPlayerCharacter(this, 0)) {
			if (abs(MainCharacter->GetActorLocation().X - this->GetActorLocation().X) > 100.0f) {
				if (this->GetActorLocation().X > MainCharacter->GetActorLocation().X) {
					AddMovementInput(FVector(-1.0f, 0.0f, 0.0f));
					this->SetActorRotation(FRotator(0.0f, 180.0f, 0.0f));
				}
				else {
					AddMovementInput(FVector(1.0f, 0.0f, 0.0f));
					this->SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));
				}
			}
		}
	}
}

void AEnemy::TurnBackAfterTime()
{
	if (!GetWorldTimerManager().IsTimerActive(TurnBackHandle)) {
		GetWorldTimerManager().SetTimer(TurnBackHandle, FTimerDelegate::CreateUObject(this, &AEnemy::TurnBackImmediate), 3.0f, false);
	}
}

void AEnemy::TurnBackImmediate()
{
	this->SetActorRotation(this->GetActorRotation() + FRotator(0.0f, 180.0f, 0.0f));
}

bool AEnemy::DetectingPatrolLimit()
{
	FHitResult PatrolLimitDetectedResult;
	FVector BoxPosition(20 * GetSprite()->GetForwardVector().X, 0, 0);
	FCollisionObjectQueryParams ObjectLookingFor;
	ObjectLookingFor.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldStatic);
	bool PatrolLimitDetected = GetWorld()->SweepSingleByObjectType(PatrolLimitDetectedResult, this->GetActorLocation() + BoxPosition, this->GetActorLocation() + BoxPosition, FQuat(0, 0, 0, 0), ObjectLookingFor, FCollisionShape::MakeBox(WallDetectBox));
	//DrawDebugBox(GetWorld(), this->GetActorLocation() + BoxPosition, WallDetectBox, FColor::Red);
	if (PatrolLimitDetected) TurnBackAfterTime();
	return PatrolLimitDetected;
}
