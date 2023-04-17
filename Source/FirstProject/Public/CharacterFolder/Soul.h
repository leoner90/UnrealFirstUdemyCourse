// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterFolder/newSpherePawn.h"
#include "Soul.generated.h"

/**
 * 
 */
UCLASS()
class FIRSTPROJECT_API ASoul : public AnewSpherePawn
{
	GENERATED_BODY()

protected:
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	UPROPERTY(EditAnywhere, Category = "Soul Properties")
	int32 Souls;

	virtual void BeginPlay() override;
public:
	FORCEINLINE int32 GetSouls() const { return Souls; }
	FORCEINLINE void SetSouls(int32 NumberOfSouls) { Souls = NumberOfSouls; }
	virtual void Tick(float DeltaTime) override;

private:
	double DesiredZ;

	UPROPERTY(EditAnywhere)
		float DriftRate = -15.f;
};
