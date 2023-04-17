 

#include "NewActorComponent.h"
#include "Components/SphereComponent.h"
 
UNewActorComponent::UNewActorComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
 

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));

 

 
}


// Called when the game starts
void UNewActorComponent::BeginPlay()
{
	Super::BeginPlay();
 
	
}


 
void UNewActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
 
}

