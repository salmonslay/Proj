// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyCharacter.h"
#include "ShadowCharacter.generated.h"

class AEnemyJumpTrigger;
class UPlayerCharState; 

/**
 * This is the state machine for the shadow versions of the characters which is almost identical to the player's
 * except for the input related functionality (there is none here) 
 */

UCLASS()
class SONDER_API AShadowCharacter : public AEnemyCharacter 
{
	GENERATED_BODY()

public:

	AShadowCharacter(); 

	/** Switches the current state to the new one */
	void SwitchState(UPlayerCharState* NewState);

	UFUNCTION(BlueprintPure)
	UPlayerCharState* GetCurrentState() const { return CurrentState; }

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Jump Debug")
	bool bCanPlatformJump = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Jump Debug")
	bool bCanBasicJump = false;

	FVector AvaliableJumpPoint = FVector::ZeroVector;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Jump Debug")
	bool bIsJumping = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Jump Debug")
	bool bHasLandedOnPlatform = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Jump Debug")
	bool bHasLandedOnGround = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Jump Debug")
	float JumpCoolDownDuration = 2.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Jump Debug")
	float JumpCoolDownTimer = 0.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Jump Debug")
	bool IsOverlappingWithTrigger = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	AEnemyJumpTrigger* CurrentJumpTrigger = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FVector ClosestJumpPoint = FVector::ZeroVector;

	FVector CurrentLocation = FVector::ZeroVector;

	UFUNCTION(BlueprintCallable)
	bool CheckIfJumpNeeded();
	
	UFUNCTION(Server, Reliable) 
	void ServerRPC_ToggleChargeEffect(const bool bActive);

	UPROPERTY(EditDefaultsOnly,  Category="Jump Debug", BlueprintReadWrite, ReplicatedUsing=OnRep_Jump)
	bool bIsPerformingJump = false;

	UFUNCTION(BlueprintCallable)
	void MakeJump();

	UFUNCTION(BlueprintCallable)
	virtual void Idle() override;
	
	UFUNCTION()
	void OnRep_Jump();

	void JumpToPoint(const FVector &JumpPoint);

	bool IsNearlyAtLocation(const FVector &Loc) const;

	UPROPERTY(BlueprintReadOnly)
	FVector CurrentTargetLocation = FVector::ZeroVector;
	
	/** Check if there's a path between the enemy character and player character*/
	bool HasNavigationToTarget(const FVector &CurrentTargetPoint) const;

	/** Calculates if jump point is closer to player than enemy*/
	bool PointCloserToPlayer(const FVector &CurrentTargetPoint) const;

	/** Checks if character is leveled with given location*/
	bool IsLeveledWithLocation(const FVector &Location) const;

	bool IsWithinRangeFrom(const FVector &Location) const;

	// EVENTS

	/** Called when a basic attack is performed, regardless if it hit something */
	UFUNCTION(BlueprintImplementableEvent)
	void OnBasicAttack();

	/** Called when the basic attack actually lands a hit, and is called for every hit */
	UFUNCTION(BlueprintImplementableEvent)
	void OnBasicAttackHit(); 
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnJumpEvent();

	UFUNCTION(BlueprintImplementableEvent)
	void OnChargeToggle(const bool bCharging); 
	
protected:

	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaSeconds) override;

	/** Returns the base state for the appropriate character */
	UPlayerCharState* GetStartingState() const; 
	
	// The player's current state - is replicated. NOTE: The state's Enter, Update, Exit etc. is only called locally 
	UPROPERTY(Replicated)
	UPlayerCharState* CurrentState = nullptr;
	
private:

	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess = true))
	float MaxHeightDifferenceToMarkAsLeveled = 70.f;

	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess = true))
	float MaxDistanceToMarkAsReachable = 200.f;

	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess = true))
	float JumpBoost = 110000.f;
	
	UFUNCTION(Server, Reliable) 
	void ServerRPC_SwitchState(UPlayerCharState* NewState); 

	UPROPERTY(EditDefaultsOnly)
	class UNiagaraSystem* ChargeEffect;

	UPROPERTY()
	class UNiagaraComponent* ChargeEffectComp;

	UPROPERTY(EditDefaultsOnly)
	class UBasicAttackComponent* EnemyAttackComp; 
	
	UFUNCTION(NetMulticast, Reliable)
	void MulticastRPC_ToggleChargeEffect(const bool bActive); 
	
};