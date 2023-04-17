// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HealthBar.generated.h"

/**
 * 
 */
UCLASS()
class FIRSTPROJECT_API UHealthBar : public UUserWidget
{
	GENERATED_BODY()
	
public:
	//the name should bar with widget variable
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* HealthBar;
};
