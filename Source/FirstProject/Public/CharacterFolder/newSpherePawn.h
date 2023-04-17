// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "newSpherePawn.generated.h"


class USphereComponent;
class UNiagaraComponent;

UCLASS()
class FIRSTPROJECT_API AnewSpherePawn : public APawn 
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AnewSpherePawn();
	int32 score;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere)
	USoundBase* counterSound;

	class AMyCharacter* character;

protected:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	class UStaticMeshComponent* ItemMesh;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//virtual to allow ovveride it in weapon class
	UFUNCTION()
	virtual	void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	virtual	void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	//
	virtual void SpawnPickupSystem();
	virtual void SpawnPickupSound();


	UPROPERTY(VisibleAnywhere)
	USphereComponent* Sphere;
	//can't accessed from child

	//NIAGRA IMPLEMENT
	UPROPERTY(EditAnywhere)
	UNiagaraComponent* EmbersEffect;

	UPROPERTY(EditAnywhere)
		USoundBase* PickupSound;

	UPROPERTY(EditAnywhere)
		class UNiagaraSystem* PickupEffect;
private:
	

	
};
