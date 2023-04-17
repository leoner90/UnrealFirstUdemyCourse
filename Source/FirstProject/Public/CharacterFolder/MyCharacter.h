// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "CharacterTypes.h"
#include "interfaces/IPickUpnterface.h"
#include "MyCharacter.generated.h"


class USpringArmComponent;
class UCameraComponent;
class AnewSpherePawn;
class UAnimMontage;
class ASoul;
class ATreasure;

UCLASS()
class FIRSTPROJECT_API AMyCharacter : public ABaseCharacter , public IIPickUpnterface
{
	GENERATED_BODY()

public:

	virtual void SetOverlappingItem(class AnewSpherePawn* Item) override;
	virtual void AddSouls(ASoul* Soul) override;
	virtual void AddGold(ATreasure* Treasure) override;

	//take damage
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	// Sets default values for this character's properties
	AMyCharacter();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool HasEnoughStamina();
	bool IsOccupied();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

 
	float GetValuess() { 
		return 1.0;
	}


	virtual void GetHit_Implementation(const FVector& ImpactPoint, AActor* Hitter) override;
	
	UPROPERTY(BlueprintReadOnly, Category = Movement)
	bool randomJump;
	
	virtual void Jump() override;
	bool IsUnoccupied();
protected:
	virtual void BeginPlay() override;
	void MoveForward(float Value);
	void Turn(float Value);
	void LookUp(float Value);
	void MoveRight(float Value);
	void EKeyPressed();
	virtual void Attack() override;
	void HideWeapon();

	
 
	UFUNCTION(BlueprintCallable)
	void StopMoving();

	//on the attack ends
	virtual void AttackEnd() override;

	//can attack?
	virtual bool CanAttack() override;

	void PlayEquipMontage(FName SectionName);
	bool CanDisarm();
	bool CanArm();

	UFUNCTION(BlueprintCallable)
		void disarm();
	UFUNCTION(BlueprintCallable)
		void armed();

	UFUNCTION(BlueprintCallable)
	void FinishEquipping();

	UFUNCTION(BlueprintCallable)
	void HitReactEnd();

	UFUNCTION(BlueprintCallable)
	void ReturnCharControl();

	virtual void Die_Implementation() override;

	
private:
	

	//when true means we overlaping something and we can make action eg. peack it up
	UPROPERTY(VisibleInstanceOnly)
	AnewSpherePawn* OverlappingItem;

	UPROPERTY(EditDefaultsOnly, Category = Montages)
	UAnimMontage* EquipMontage;

	float Scoressss = 0;
	//CAMERA AND SPRING ARM
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* ViewCamera;

	//Widget
	UPROPERTY()
	class USlashOverlay* SlashOverlay;

	void InitializeSlashOverlay();

	void SetHUDHealth();
 
public: 
	//ECS_Unequipped default state
	ECharacterState CharacterState = ECharacterState::ECS_Unequipped;
	EActionState ActionState = EActionState::EAS_Unoccupied;

	//FORCEINLINE - will make inline function on compile
	//FORCEINLINE void SetOverlappingItem(AnewSpherePawn* AnewSpherePawn) { OverlappingItem = AnewSpherePawn; }
	FORCEINLINE float GetScore() { return Scoressss; }
	FORCEINLINE void SetScore(float score) { Scoressss += score; }
	FORCEINLINE ECharacterState GetCharacterState() const { return CharacterState; }
	FORCEINLINE EActionState GetActionState() const { return ActionState; }

	void Dodge();
	virtual void DodgeEnd() override;
};
