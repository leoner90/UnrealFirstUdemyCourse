// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CharacterFolder/CharacterTypes.h"
#include "CoreMinimal.h"
#include "CharacterFolder/BaseCharacter.h"
#include "Enemy.generated.h"

UCLASS()
class FIRSTPROJECT_API AEnemy : public ABaseCharacter
{
	GENERATED_BODY()

public:
	//Fun first then variables
	AEnemy(); // constuctor shoul be public
	virtual void Tick(float DeltaTime) override;

	//patrol
	void CheckPatrolTarget();
	void CheckCombatTarget();

	//virtual void GetHit(const FVector& ImpactPoint) override; in case to use in BP 
	virtual void GetHit_Implementation(const FVector& ImpactPoint, AActor* Hitter) override;

	//DAMAGE
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	
	//On pawn destoyed ovvveride
	virtual void Destroyed() override;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	EEnemyState EnemyState = EEnemyState::EES_Patrolling;


	UPROPERTY(EditAnywhere, Category = Combat)
	TSubclassOf<class ASoul> SoulClass;

	void SpawnSoul();

	UPROPERTY(EditAnywhere, Category = Combat)
		double AcceptanceRadius = 50.f;

protected:
	virtual void BeginPlay() override;

	//die handler
	virtual void Die_Implementation() override;

	//patroll
	bool InTargetRange(AActor* Target, double Radius);



	void MoveToTarget(AActor* Target);
	AActor* ChoosePatrolTarget();

	UFUNCTION()
	void PawnSeen(APawn* SeenPawn);

	//ATACK
	virtual void Attack() override;
	virtual bool CanAttack() override;
	virtual void HandleDamage(float DamageAmount) override;

	UPROPERTY(EditAnywhere, Category = Combat)
	float DeathLifespan = 8.f;
 

	
private:

	UPROPERTY(VisibleAnywhere)
	class UPawnSensingComponent* PawnSensing;

	//Widget
	UPROPERTY(VisibleAnywhere)
	class UHealthBarComponent* HealthBarWidget;



	UPROPERTY(EditAnywhere)
	double CombatRadius = 1000.f;
	
	UPROPERTY(EditAnywhere)
	double AttackRadius = 400.f;

	//Patroll
	UPROPERTY(EditAnywhere)
	double PatrolRadius = 400.f;

	FTimerHandle PatrolTimer;
	void PatrolTimerFinished();

	UPROPERTY(EditAnywhere, Category = "AI Navigation")
	float WaitMin = 1.f;

	UPROPERTY(EditAnywhere, Category = "AI Navigation")
	float WaitMax = 3.f;

	UPROPERTY()
	class AAIController* EnemyController;

	// Current patrol target
	UPROPERTY(EditInstanceOnly, Category = "AI Navigation")
	AActor* PatrolTarget;

	UPROPERTY(EditInstanceOnly, Category = "AI Navigation")
	TArray<AActor*> PatrolTargets;

	bool isDead = false;

	//Enemy Weapon
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AWeapon> WeaponClass;

	//AI BEHAVIOR
	void HideHealthBar();
	void ShowHealthBar();
	void LoseInterest();
	void StartPatroling();
	void ChaseTarget();
	bool IsOutsideCombatRadius();
	bool IsOutsideAttackRadius();
	bool IsInsideAttackRadius();
	bool IsChasing();
	bool IsAttacking();
	bool IsDead();
	bool IsEngaged();
	void ClearPatrolTimer();

	//Combat
	void StartAttackTimer();
	void ClearAttackTimer();
	FTimerHandle AttackTimer;
	UPROPERTY(EditAnywhere, Category = Combat)
	float AttackMin = 0.5f;
	UPROPERTY(EditAnywhere, Category = Combat)
	float AttackMax = 1.f;

	UPROPERTY(EditAnywhere, Category = Combat)
	float PatrolingSpeed = 125.f;
	UPROPERTY(EditAnywhere, Category = Combat)
	float ChasingSpeed = 300.f;

	virtual void AttackEnd() override;
};
