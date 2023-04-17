 
//TO START WIDGET set HUD ON BEGIN PLAY
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SlashHUD.generated.h"

class USlashOverlay;

UCLASS()
class FIRSTPROJECT_API ASlashHUD : public AHUD
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;
private:
	UPROPERTY(EditDefaultsOnly, Category = Slash)
	TSubclassOf<USlashOverlay> SlashOverlayClass;

	UPROPERTY()
	USlashOverlay* SlashOverlay;
public:
	//just getter function
	FORCEINLINE USlashOverlay* GetSlashOverlay() const { return SlashOverlay; }
};
