#pragma once



//alow in BP
UENUM(BlueprintType)
enum class ECharacterState : uint8

	//ECS_ just abriviature of enum class to avoid same constanst name in diferents enum
	//uint8 can be only positive?
{//UMETA just to give a name in BP to make it look better when ECS_Unequipped is a constant name
	ECS_Unequipped UMETA(DisplayName = "Unequipped"),
	ECS_EquippedOneHandedWeapon UMETA(DisplayName = "Equipped One-Handed Weapon"),
	ECS_EquippedTwoHandedWeapon UMETA(DisplayName = "Equipped Two-Handed Weapon"),
	ECS_OnTheBack UMETA(DisplayName = "OnTheBack")
};

UENUM(BlueprintType)
enum class EActionState : uint8
{
	EAS_Unoccupied UMETA(DisplayName = "Unoccupied"),
	AS_HitReaction UMETA(DisplayName = "HitReaction"),
	EAS_Jump UMETA(DisplayName = "Jump"),
	EAS_Attacking UMETA(DisplayName = "Attacking"),
	EAS_EquipingWeapon UMETA(DisplayName = "Equiping Weapon"),
	EAS_Dodge UMETA(DisplayName = "Dodge"),
	EAS_Dead UMETA(DisplayName = "CharDead")
};

UENUM(BlueprintType)
enum EDeathPose 
{
	EDP_Death1 UMETA(DisplayName = "Death1"),
	EDP_Death2 UMETA(DisplayName = "Death2"),
	EDP_Max UMETA(DisplayName = "DefaulMax")
};



UENUM(BlueprintType)
enum class EEnemyState : uint8
{
	EES_NoState UMETA(DisplayName = "NoState"),
	EES_Dead UMETA(DisplayName = "Dead"),
	EES_Patrolling UMETA(DisplayName = "Patrolling"),
	EES_Chasing UMETA(DisplayName = "Chasing"),
	EES_Attacking UMETA(DisplayName = "Attacking"),
	EES_Engaged UMETA(DisplayName = "Engaged")
	
};