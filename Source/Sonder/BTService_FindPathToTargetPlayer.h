// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_FindPathToTargetPlayer.generated.h"

class AFlyingEnemyCharacter;
class AGrid;
/**
 * 
 */
UCLASS()
class SONDER_API UBTService_FindPathToTargetPlayer : public UBTService_BlackboardBase
{
	GENERATED_BODY()

				
public: /** Constructor*/
	UBTService_FindPathToTargetPlayer();
	
protected:
	/** Tick node is called every tick service is in progress*/
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY()
	AFlyingEnemyCharacter* OwnerCharacter;

	FVector OwnerLocation;

	UPROPERTY()
	AGrid* OwnerGrid = nullptr;

	UPROPERTY(EditAnywhere)
	bool bDebug = false;

	FVector CurrentTargetLocation = FVector::ZeroVector;

	FVector OldTargetLocation = FVector::ZeroVector;

	TArray<FVector> Path = TArray<FVector>();
};
