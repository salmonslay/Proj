// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_FollowPath.generated.h"

class AGrid;
class AFlyingEnemyCharacter;
/**
 * 
 */
UCLASS()
class SONDER_API UBTTask_FollowPath : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:

	/** Constructor*/
	UBTTask_FollowPath();

	/** Execute task is called once every time this task is activated */
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	/** Tick task is called every tick this task is in progress, set up in execute task */
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY()
	TWeakObjectPtr<AFlyingEnemyCharacter> OwnerCharacter;

	UPROPERTY()
	TWeakObjectPtr<AGrid> OwnerGrid = nullptr;

	FVector OwnerLocation;
	FVector CurrentTargetLocation;

	UPROPERTY(EditAnywhere)
	bool bDebug = false;
	
	UPROPERTY(EditAnywhere)
	float PathFollowingSpeed = 100.f;
};
