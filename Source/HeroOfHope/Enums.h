// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EPlayerAbilityInputID : uint8 {
	None,
	Confirm,
	Cancel,
	Attack,
	Jump,
};

