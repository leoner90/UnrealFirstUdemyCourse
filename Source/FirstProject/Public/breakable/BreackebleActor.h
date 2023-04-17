// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "interfaces/HitInterface.h"
#include "BreackebleActor.generated.h"

class UGeometryCollectionComponent;

UCLASS()
class FIRSTPROJECT_API ABreackebleActor : public AActor, public IHitInterface
{
	GENERATED_BODY()
	
public:	
	ABreackebleActor();
	virtual void Tick(float DeltaTime) override;

	//virtual void GetHit(const FVector& ImpactPoint) override;
	virtual void GetHit_Implementation(const FVector& ImpactPoint, AActor* Hitter) override;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UGeometryCollectionComponent* GeometryCollection;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UCapsuleComponent* Capsule;
	
protected:
	virtual void BeginPlay() override;

	
private:


	UPROPERTY(EditAnywhere, Category = "Breakable Properties")
		//TSubclassOf to put restriction anything derifed from tresure, as a wrapper - stores pointer
		//TSubclassOf<class ATreasure> TreasureClass;
		//TArray same but for multiply inputs
		TArray<TSubclassOf<class ATreasure>> TreasureClasses;
	//to avoid infinit calling loop
	bool bBroken = false;
};
