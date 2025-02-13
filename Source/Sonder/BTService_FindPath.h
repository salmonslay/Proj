// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_FindPath.generated.h"

class AFlyingEnemyCharacter;
class AGrid;
/**
 * 
 */
UCLASS()
class SONDER_API UBTService_FindPath : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:

	UBTService_FindPath();
	
protected:
	/** Tick node is called every tick service is in progress*/
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
	UPROPERTY()
	AFlyingEnemyCharacter* OwnerCharacter;

	FVector OwnerLocation;

	UPROPERTY()
	UBlackboardComponent* BlackboardComponent;

	UPROPERTY()
	AGrid* OwnerGrid = nullptr;

	UPROPERTY(EditAnywhere)
	bool bDebug = false;

	FVector CurrentTargetLocation = FVector::ZeroVector;

	TArray<FVector> Path = TArray<FVector>();
};
