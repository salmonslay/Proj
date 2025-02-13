// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_AttackPlayer.generated.h"

class AEnemyCharacter;
/**
 * 
 */
UCLASS()
class SONDER_API UBTTask_AttackPlayer : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:

	/** Constructor*/
	UBTTask_AttackPlayer();

	/** Execute task is called once every time this task is activated */
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	/** Tick task is called every tick this task is in progress, set up in execute task */
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY()
	AEnemyCharacter* OwnerCharacter;

	FVector OwnerLocation;

	UPROPERTY(EditAnywhere)
	bool bDebug = false;
	
};
