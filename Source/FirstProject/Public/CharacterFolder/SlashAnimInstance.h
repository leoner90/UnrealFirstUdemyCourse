// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CharacterFolder/CharacterTypes.h"
#include "SlashAnimInstance.generated.h"


/**
 *
 */
UCLASS()
class FIRSTPROJECT_API USlashAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	//Same as in BP On Anim Start
	virtual void NativeInitializeAnimation() override;
	////Same as in BP on tick
	virtual void NativeUpdateAnimation(float DeltaTime) override;

	UPROPERTY(BlueprintReadOnly)
		class AMyCharacter* SlashCharacter;

	UPROPERTY(BlueprintReadOnly)
		class UCharacterMovementComponent* SlashCharacterMovement;

	UPROPERTY(BlueprintReadOnly, Category = Movement)
		float GroundSpeed;

	UPROPERTY(BlueprintReadOnly, Category = Movement)
		bool IsFalling;

	UPROPERTY(BlueprintReadOnly, Category = Movement)
		ECharacterState CharacterState;

	UPROPERTY(BlueprintReadOnly, Category = Movement)
		TEnumAsByte<EDeathPose> DeathPose;

	UPROPERTY(BlueprintReadOnly, Category = Movement)
	EActionState ActionState;
};
