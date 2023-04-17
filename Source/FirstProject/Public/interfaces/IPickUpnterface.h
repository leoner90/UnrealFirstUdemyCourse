// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IPickUpnterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UIPickUpnterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class FIRSTPROJECT_API IIPickUpnterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void SetOverlappingItem(class AnewSpherePawn* Item);
	virtual void AddSouls(class ASoul* Soul);
	virtual void AddGold(class ATreasure* Treasure);
};
