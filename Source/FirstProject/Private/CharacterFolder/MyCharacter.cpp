// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterFolder/MyCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "CharacterFolder/newSpherePawn.h"
#include "Weapon/Weapon.h"
#include "Animation/AnimMontage.h"
#include "GameFramework/Character.h"
#include "Components/StaticMeshComponent.h"

//widgets Update
#include "HUD/SlashHUD.h"
#include "HUD/SlashOverlay.h"
#include "Components/AttributeComponent.h"

#include "CharacterFolder/Soul.h"
#include "CharacterFolder/Treasure.h"

void AMyCharacter::SetOverlappingItem(AnewSpherePawn* Item)
{
	OverlappingItem = Item;
}

void AMyCharacter::AddSouls(ASoul* Soul)
{
	if (Attributes && SlashOverlay)
	{
		Attributes->AddSouls(Soul->GetSouls());
		SlashOverlay->SetSouls(Attributes->GetSouls());
	}
}

void AMyCharacter::AddGold(ATreasure* Treasure)
{
	if (Attributes && SlashOverlay)
	{
		Attributes->AddGold(Treasure->GetGold());
		SlashOverlay->SetGold(Attributes->GetGold());
	}
}

float AMyCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	HandleDamage(DamageAmount);
	SetHUDHealth();
	return DamageAmount;
}

// Sets default values
AMyCharacter::AMyCharacter()
{
	//Setting for a proper wepaon hit response 
	GetMesh()->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	GetMesh()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore); // ignore all and then sset what we need 
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Overlap);
	GetMesh()->SetGenerateOverlapEvents(true);

 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//buleans starts from lower b.
	bUseControllerRotationPitch = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	//IN BP !!!!!! bUsePawnControlRotation = true;
	//orienttation check BOX in BP
	GetCharacterMovement()->bOrientRotationToMovement = true;
	//RotationRate
	GetCharacterMovement()->RotationRate = FRotator(0.f, 360.f, 0.f);
 

	//Spring(cameraBoom) Arm CAMERA
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 380.f;


	//Camera Itself
	ViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ViewCamera"));
	ViewCamera->SetupAttachment(CameraBoom);
	
	//insert into object
	AutoPossessPlayer = EAutoReceiveInput::Player0;

}

void AMyCharacter::GetHit_Implementation(const FVector& ImpactPoint , AActor* Hitter)
{

	Super::GetHit_Implementation(ImpactPoint, Hitter);

	if (Attributes && Attributes->GetHealthPercent() > 0.f)
	{
		ActionState = EActionState::AS_HitReaction;
	}
	SetWeaponCollisionEnabled(ECollisionEnabled::NoCollision);
	
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	Tags.Add(FName("SlashCharacter"));
	InitializeSlashOverlay();
}
/*
* MOVEMANT
**/
void AMyCharacter::MoveForward(float Value)
{
	if (ActionState != EActionState::EAS_Unoccupied) return;
	if ((Controller != nullptr) && (Value != 0.f))
	{
	 
		//find which way is forward according to controler vector(mouse)?
		const FRotator ControlRotation = GetControlRotation();
		const FRotator YawRotation(0.f, ControlRotation.Yaw, 0.f);
		//return vector unit of 1
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AMyCharacter::Turn(float Value)
{
	AddControllerYawInput(Value);
}

void AMyCharacter::LookUp(float Value)
{
	AddControllerPitchInput(Value);
}

void AMyCharacter::MoveRight(float Value)
{
	if (ActionState != EActionState::EAS_Unoccupied) return;
	if ((Controller != nullptr) && (Value != 0.f))
	{
		//old
		//FVector Right = GetActorRightVector();
		//just pass the derection of movement if u pass 2 speed will not increase
		//AddMovementInput(Right, Value);
		//find which way is Right according to controler vector(mouse)?
		const FRotator ControlRotation = GetControlRotation();
		const FRotator YawRotation(0.f, ControlRotation.Yaw, 0.f);
		//return vector unit of 1
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

/**
* Pick UP Weapon
*/
void AMyCharacter::EKeyPressed()
{
	AWeapon* OverlappingWeapon = Cast<AWeapon>(OverlappingItem);
	if (OverlappingWeapon)
	{
		if (EquippedWeapon)
		{
			EquippedWeapon->Destroy();
		}
		OverlappingWeapon->Equip(GetMesh(), FName("rightHandSocket"), this, this);
		CharacterState = ECharacterState::ECS_EquippedOneHandedWeapon;
		//setting overlaping obj to nuull
		OverlappingItem = nullptr;
		EquippedWeapon = OverlappingWeapon;
	}
}

void AMyCharacter::PlayEquipMontage(FName SectionName)
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && EquipMontage)
	{
		AnimInstance->Montage_Play(EquipMontage);
		AnimInstance->Montage_JumpToSection(SectionName, EquipMontage);
	}
}

/**
* ATTACK ANIMATION
*/
void AMyCharacter::Attack()
{
	Super::Attack();
	
	if (CanAttack())
	{
		PlayAttackMontage();
		ActionState = EActionState::EAS_Attacking;
	}
	
}

bool AMyCharacter::CanAttack()
{
	return ActionState == EActionState::EAS_Unoccupied &&
		CharacterState != ECharacterState::ECS_Unequipped &&
		CharacterState != ECharacterState::ECS_OnTheBack;
}


void AMyCharacter::AttackEnd()
{
	ActionState = EActionState::EAS_Unoccupied;
}
  

/**
* Weapon Equip and hide annimation
*/

void AMyCharacter::HideWeapon()
{
	if (CanDisarm())
	{
		PlayEquipMontage(FName("Unequip"));
		CharacterState = ECharacterState::ECS_OnTheBack;
		ActionState = EActionState::EAS_EquipingWeapon;
	}
	else if (CanArm())
	{
		PlayEquipMontage(FName("Equip"));
		CharacterState = ECharacterState::ECS_EquippedOneHandedWeapon;
		ActionState = EActionState::EAS_EquipingWeapon;
	}
}

bool AMyCharacter::CanDisarm()
{
	return ActionState == EActionState::EAS_Unoccupied &&
		CharacterState != ECharacterState::ECS_Unequipped &&
		CharacterState != ECharacterState::ECS_OnTheBack;
	
}

bool AMyCharacter::CanArm()
{
	return ActionState == EActionState::EAS_Unoccupied &&
		CharacterState == ECharacterState::ECS_OnTheBack;
 
		EquippedWeapon;
}

void AMyCharacter::disarm()
{
	if (EquippedWeapon) 
	{
		EquippedWeapon->AttachMeshToSocket(GetMesh(), FName("spine_Socket"));
	}
}

void AMyCharacter::armed()
{
	if (EquippedWeapon)
	{
		EquippedWeapon->AttachMeshToSocket(GetMesh(), FName("rightHandSocket"));
	}
}

void AMyCharacter::FinishEquipping()
{
	ActionState = EActionState::EAS_Unoccupied;
}



// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	//Super::Tick(DeltaTime);
	if (Attributes && SlashOverlay)
	{
		Attributes->RegenStamina(DeltaTime);
		SlashOverlay->SetStaminaBarPercent(Attributes->GetStaminaPercent());
	}
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(FName("MoveForward"), this, &AMyCharacter::MoveForward);
	PlayerInputComponent->BindAxis(FName("Turn"), this, &AMyCharacter::Turn);
	PlayerInputComponent->BindAxis(FName("LookUp"), this, &AMyCharacter::LookUp);
	PlayerInputComponent->BindAxis(FName("MoveRight"), this, &AMyCharacter::MoveRight);
	//&ACharacter::Jump VIRTUAL FUNCTION IN CHARACTER CLASS
	PlayerInputComponent->BindAction(FName("Jump"), IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(FName("Equip"), IE_Pressed, this, &AMyCharacter::EKeyPressed);
	PlayerInputComponent->BindAction(FName("Attack"), IE_Pressed, this, &AMyCharacter::Attack);
	PlayerInputComponent->BindAction(FName("hideWeapon"), IE_Pressed, this, &AMyCharacter::HideWeapon);
	PlayerInputComponent->BindAction(FName("Dodge"), IE_Pressed, this, &AMyCharacter::Dodge);
}

void AMyCharacter::Dodge()
{
	if (ActionState != EActionState::EAS_Unoccupied) return;
	if (IsOccupied() || !HasEnoughStamina()) return;

	if (ActionState != EActionState::EAS_Unoccupied) return;
	PlayDodgeMontage();
	ActionState = EActionState::EAS_Dodge;
	if (Attributes && SlashOverlay)
	{
		Attributes->UseStamina(Attributes->GetDodgeCost());
		SlashOverlay->SetStaminaBarPercent(Attributes->GetStaminaPercent());
	}
}


bool AMyCharacter::HasEnoughStamina()
{
	return Attributes && Attributes->GetStamina() > Attributes->GetDodgeCost();
}

bool AMyCharacter::IsOccupied()
{
	return ActionState != EActionState::EAS_Unoccupied;
}

void AMyCharacter::DodgeEnd()
{
	Super::DodgeEnd();

	ActionState = EActionState::EAS_Unoccupied;
}


void AMyCharacter::Jump() {
	
	if (IsUnoccupied()) {
		Super::Jump();
	}
}

bool AMyCharacter::IsUnoccupied()
{
	return ActionState == EActionState::EAS_Unoccupied;
}

void AMyCharacter::StopMoving()
{
	ActionState = EActionState::EAS_Jump;
}

void AMyCharacter::ReturnCharControl()
{
	ActionState = EActionState::EAS_Unoccupied;
	randomJump = true;
}

void AMyCharacter::InitializeSlashOverlay()
{
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController)
	{
		ASlashHUD* SlashHUD = Cast<ASlashHUD>(PlayerController->GetHUD());
		if (SlashHUD)
		{
			SlashOverlay = SlashHUD->GetSlashOverlay();
			if (SlashOverlay && Attributes)
			{
				SlashOverlay->SetHealthBarPercent(Attributes->GetHealthPercent());
				SlashOverlay->SetStaminaBarPercent(1.f);
				SlashOverlay->SetGold(0);
				SlashOverlay->SetSouls(0);
			}
		}
	}
}

void AMyCharacter::HitReactEnd()
{
	ActionState = EActionState::EAS_Unoccupied;
}


void AMyCharacter::SetHUDHealth()
{
	if (SlashOverlay && Attributes)
	{
		SlashOverlay->SetHealthBarPercent(Attributes->GetHealthPercent());
	}
}

void AMyCharacter::Die_Implementation()
{
	Super::Die_Implementation();
	ActionState = EActionState::EAS_Dead;
	DisableMeshCollision();
}