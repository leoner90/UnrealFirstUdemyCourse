// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterFolder/Treasure.h"
//#include "CharacterFolder/MyCharacter.h"
#include "interfaces/IPickUpnterface.h"
 

void ATreasure::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	IIPickUpnterface* PickupInterface = Cast<IIPickUpnterface>(OtherActor);
	if (PickupInterface)
	{
		PickupInterface->AddGold(this);
		
		SpawnPickupSound();
		Destroy();
	}
}
