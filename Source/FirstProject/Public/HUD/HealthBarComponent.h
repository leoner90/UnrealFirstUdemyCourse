// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "HealthBarComponent.generated.h"

/**
 * 
 */
UCLASS()
class FIRSTPROJECT_API UHealthBarComponent : public UWidgetComponent
{
	GENERATED_BODY()
public:
	void SetHealthPercent(float Percent);
private:
	//as cast to componet is very expesive as it goes up to hierary in case of fail we need to do this - memeber variable
	//not start as uninisilized with garbige data  
	UPROPERTY()
		class UHealthBar* HealthBarWidget;
};
