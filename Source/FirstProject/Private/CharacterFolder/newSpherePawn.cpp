// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterFolder/newSpherePawn.h"
#include "Components/SphereComponent.h"
#include "interfaces/IPickUpnterface.h"
#include "Components/ActorComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AnewSpherePawn::AnewSpherePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//creating mesh
	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMeshComponent"));
	RootComponent = ItemMesh;

	//creating a sphere
	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetupAttachment(GetRootComponent());

	//NIAGRAA
	EmbersEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Embers"));
	EmbersEffect->SetupAttachment(GetRootComponent());

	ItemMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	ItemMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void AnewSpherePawn::BeginPlay()
{
	Super::BeginPlay();

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AnewSpherePawn::OnSphereOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &AnewSpherePawn::OnSphereEndOverlap);
}
 
void AnewSpherePawn::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//const FString OtherActorName = OtherActor->GetName();
	if (GEngine)
	{
 
		//Checking who is overlaping is it our character class //if yes ctr shift space to see inputs
		IIPickUpnterface* PickupInterface = Cast<IIPickUpnterface>(OtherActor);
		if (PickupInterface)
		{
			PickupInterface->SetOverlappingItem(this);
		}
	}
}

void AnewSpherePawn::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//Checking who is overlaping is it our character class
	
	//if yes ctr shift space to see inputs
	IIPickUpnterface* PickupInterface = Cast<IIPickUpnterface>(OtherActor);
	if (PickupInterface)
	{
		PickupInterface->SetOverlappingItem(nullptr);
	}

	//AMyCharacter* SlashCharacter = Cast<AMyCharacter>(OtherActor);
	//if (GEngine)
	//{
		//SoundPlay
		//UGameplayStatics::SpawnSoundAtLocation(this, counterSound, GetActorLocation());
		//if (SlashCharacter) {
			//SlashCharacter->SetScore(1);
			//float test = SlashCharacter->GetScore();
		//}
	//}
}

// Called every frame
void AnewSpherePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AnewSpherePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}



void AnewSpherePawn::SpawnPickupSystem()
{
	if (PickupEffect)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(
			this,
			PickupEffect,
			GetActorLocation()
		);
	}
}

void AnewSpherePawn::SpawnPickupSound()
{
	if (PickupSound)
	{
		UGameplayStatics::SpawnSoundAtLocation(
			this,
			PickupSound,
			GetActorLocation()
		);
	}
}