// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterFolder/newSpherePawn.h"
#include "Weapon.generated.h"
class USoundBase;
class  UBoxComponent;
/**
 * 
 */
UCLASS()

//extended from AnewSpherePawn123
class FIRSTPROJECT_API AWeapon : public AnewSpherePawn
{
	GENERATED_BODY()
public:
	AWeapon();//constuctor
	void Equip(USceneComponent* InParent, FName InSocketName,AActor* NewOwner, APawn* NewInstigator);
	void DiactivateEmbers();
	void DisableSphereCollision();
	void PlayEquipSound();
	void AttachMeshToSocket(USceneComponent* InParent, const FName& InSocketName);

	//scene component , to trace berween to line , if something is between it's trigers
	UPROPERTY(VisibleAnywhere)
		USceneComponent* BoxTraceStart;

	UPROPERTY(VisibleAnywhere)
		USceneComponent* BoxTraceEnd;

	FORCEINLINE UBoxComponent* GetWeaponBox() const { return WeaponBox; }

	UPROPERTY(EditAnywhere, Category = "Weapon Properties")
		UBoxComponent* WeaponBox;
	TArray<AActor*> IgnoreActors;
private:
	UPROPERTY(EditAnywhere, Category = "Weapon Properties")
		USoundBase* EquipSound;
	

	//DAMAGE
	UPROPERTY(EditAnywhere, Category = "Weapon Properties")
	float Damage = 10.f;
	
	void BoxTrace(FHitResult& BoxHit);

	UPROPERTY(EditAnywhere, Category = "Weapon Properties")
	FVector BoxTraceExtent = FVector(5.f);

	UPROPERTY(EditAnywhere, Category = "Weapon Properties")
	bool bShowBoxDebug = false;


protected:
	virtual void BeginPlay() override;
	virtual	void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;
	
	UFUNCTION()
	void OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	bool ActorIsSameType(AActor* OtherActor);
	bool ActorIsSameType2(AActor* OtherActor);

	void ExecuteGetHit(FHitResult& BoxHit);
	
	UFUNCTION(BlueprintImplementableEvent)
	void CreateFields(const FVector& FieldLocation);
};
