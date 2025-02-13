// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_ChooseAttack.generated.h"

/**
 * Service updates which attack should be performed (special (Pulse/dash) or basic attack) 
 */
UCLASS()
class SONDER_API UBTService_ChooseAttack : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:

	/** How far away the AI needs to be to its target to perform the special attack */
	UPROPERTY(EditAnywhere)
	float DistanceToSpecialAttack = 250.f;

	/** How far away the AI needs to be to its target to perform basic attack */
	UPROPERTY(EditAnywhere)
	float DistanceToBasicAttack = 50.f;

	/** Probability to perform special attack (Pulse/Dash) when in range */
	UPROPERTY(EditAnywhere)
	float ProbabilityToSpecialAttack = 0.75f; 

	/** Probability to do basic attack when within basic attack range */ 
	UPROPERTY(EditAnywhere)
	float ProbabilityToBasicAttack = 0.75f;

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector BBKeyDoBasicAttack;

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector BBKeyDoSpecialAttack;

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector BBKeyCurrentTarget;
	
	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector BBKeyChargingSpecialAttack;

	UPROPERTY()
	class UBasicAttackComponent* AttackComp;

	UPROPERTY()
	class URobotBaseState* RobotState;

	UPROPERTY()
	class USoulBaseStateNew* SoulState;

	bool bHasSetUpComps = false; 

	/** Returns true if the AI is charging or using its special attack (dash) */
	bool IsUsingSpecialAttack(UBehaviorTreeComponent& OwnerComp) const; 

	/** Returns true if the Owner's special attack (Pulse or Dash) is on cooldown and cant be performed */
	bool IsSpecialAttackOnCooldown(const APawn* Owner) const;

	/** Returns true if the Owner's basic attack is on cooldown and cant be performed */
	bool CanBasicAttack(const APawn* Owner) const; 

	/** Returns true if the AI is in range to perform basic attack */
	bool IsInRangeForBasicAttack(const float DistanceToTarget) const;

	/** Sets/Clears the basic attack BB Key based on passed bool */
	void SetBasicAttackBBKey(UBehaviorTreeComponent& OwnerComp, const bool bCanDoAttack) const;

	/** Sets/Clears the basic attack BB Key based on passed bool */
	void SetSpecialAttackBBKey(UBehaviorTreeComponent& OwnerComp, const bool bCanDoAttack) const; 
	
};
