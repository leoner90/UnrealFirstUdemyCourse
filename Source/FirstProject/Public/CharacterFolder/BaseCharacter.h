// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "interfaces/HitInterface.h"
#include "CharacterFolder/CharacterTypes.h"
#include "BaseCharacter.generated.h"

UCLASS()
class FIRSTPROJECT_API ABaseCharacter : public ACharacter, public IHitInterface
{
	GENERATED_BODY()

public:
	ABaseCharacter();
	virtual void Tick(float DeltaTime) override;

	//Weapon Collisions
	UFUNCTION(BlueprintCallable)
	void SetWeaponCollisionEnabled(ECollisionEnabled::Type CollisionEnabled);

	FORCEINLINE TEnumAsByte<EDeathPose> GetDeathPose() const { return DeathPose; }
	void DisableMeshCollision();
protected:
	virtual void BeginPlay() override;

	//equipt weapon
	UPROPERTY(VisibleAnywhere, Category = Weapon)
	class AWeapon* EquippedWeapon;

	//is possible to make attack
	virtual bool CanAttack();
	//isALive
	bool IsAlive();
	//atack
	virtual void Attack();

	//on the attack ends
	UFUNCTION(BlueprintCallable)
	virtual	void AttackEnd();

	// Attack montages 
	UPROPERTY(EditDefaultsOnly, Category = Montages)
	UAnimMontage* AttackMontage;

	// Animation montages 
	UPROPERTY(EditDefaultsOnly, Category = Montages)
	class UAnimMontage* HitReactMonatge;

	//Play montage functions
	void PlayHitReactMontage(const FName& SectionName);

	//die handler
	//virtual void Die();
	//accesble from BP
	UFUNCTION(BlueprintNativeEvent)
	void Die();

	//from which side atack was made
	void DirectionalHitReact(const FVector& ImpactPoint);

	//HealthBar
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UAttributeComponent* Attributes;

	//HIT SOUND
	UPROPERTY(EditAnywhere, Category = Sounds)
	USoundBase* HitSound;

	//VFX Effects , no need to forward declare , it build in
	UPROPERTY(EditAnywhere, Category = VisualEffects)
	UParticleSystem* HitParticles;

	//play Sound On Hit
	void PlayHitSound(const FVector& ImpactPoint);
	void SpawnHitParticles(const FVector& ImpactPoint);
	virtual void HandleDamage(float DamageAmount);

	//Montage Handler
	void PlayMontageSection(UAnimMontage* Montage , const FName& SectionName);

	//Play Attack montage functions
	virtual int32 PlayAttackMontage();

	//ATACK MOntage Section
	UPROPERTY(EditAnywhere, Category = Combat)
	TArray<FName> AttackMontageSections;
	int32 PlayRandomMontageSection(UAnimMontage* Montage, const TArray<FName>& SectionNames);

	//Death MOntage Section

	UPROPERTY(EditAnywhere, Category = Combat)
	TArray<FName> DeathMontageSections;
	virtual int32 PlayDeathMontage();

	//DeathMontage
	UPROPERTY(EditDefaultsOnly, Category = Montages)
	class UAnimMontage* DeathMontage;

	//Disable capsule Collision 
	void DisableCapsule();

	//Get Hit
	virtual void GetHit_Implementation(const FVector& ImpactPoint, AActor* Hitter) override;

	//stop montage
	void StopAttackMontage();


	//Warp Target To rotation
	UFUNCTION(BlueprintCallable)
	FVector GetTranslationWarpTarget();

	UFUNCTION(BlueprintCallable)
	FVector GetRotationWarpTarget();

	UPROPERTY(EditAnywhere, Category = Combat)
	double WarpTargetDistance = 75.f;

	UPROPERTY(BlueprintReadOnly, Category = Combat)
	AActor* CombatTarget;

	//Death Poses
	UPROPERTY(BlueprintReadOnly)
	TEnumAsByte<EDeathPose> DeathPose;

	virtual void PlayDodgeMontage();

	UFUNCTION(BlueprintCallable)
		virtual void DodgeEnd();

	UPROPERTY(EditDefaultsOnly, Category = Combat)
		UAnimMontage* DodgeMontage;

};
