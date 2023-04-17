// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/SlashHUD.h"
#include "HUD/SlashOverlay.h"

void ASlashHUD::BeginPlay()
{
	Super::BeginPlay();

	UWorld* World = GetWorld();
	if (World)
	{
		// in sigle play games there is only one controler , and we grab it here
		APlayerController* Controller = World->GetFirstPlayerController();
		if (Controller && SlashOverlayClass)
		{
			//our BP widget with all the hud
			SlashOverlay = CreateWidget<USlashOverlay>(Controller, SlashOverlayClass);
			//exists as a member variable on HUD class , what we can acces to call our public function
			SlashOverlay->AddToViewport();
		}
	}
}