

#include "breakable/BreackebleActor.h"
#include "GeometryCollection/GeometryCollectionComponent.h"
#include "Components/CapsuleComponent.h"
#include "CharacterFolder/Treasure.h"

ABreackebleActor::ABreackebleActor()
{

	PrimaryActorTick.bCanEverTick = false;
	GeometryCollection = CreateDefaultSubobject<UGeometryCollectionComponent>(TEXT("GeometryCollection"));
	SetRootComponent(GeometryCollection);
	GeometryCollection->SetGenerateOverlapEvents(true);
	GeometryCollection->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);


	//spawn actor section
	GeometryCollection->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	Capsule->SetupAttachment(GetRootComponent());
	Capsule->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	Capsule->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);
}

void ABreackebleActor::BeginPlay()
{
	Super::BeginPlay();

	//GeometryCollection->OnChaosBreakEvent.AddDynamic(this,)
	
}

void ABreackebleActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABreackebleActor::GetHit_Implementation(const FVector& ImpactPoint, AActor* Hitter)
{
	//execute function only once
	if (bBroken) return;
	bBroken = true;

	UWorld* World = GetWorld();
	//check that classes array is not empty
	if (World && TreasureClasses.Num() > 0)
	{
		FVector Location = GetActorLocation();
		Location.Z += 15.f;
		Location.X += 75.f;
		//ESpawnActorCollisionHandlingMethod::AlwaysSpawn
		//TreasureClass can be selected in BP
	 

		// if single objects World->SpawnActor<ATreasure>(TreasureClass, Location, GetActorRotation());

		//random select treasure 
		const int32 Selection = FMath::RandRange(0, TreasureClasses.Num() - 1);
		World->SpawnActor<ATreasure>(TreasureClasses[Selection], Location, GetActorRotation());
		
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("HIT Vase"));


	}
}