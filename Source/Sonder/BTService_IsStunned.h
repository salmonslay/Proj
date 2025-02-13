// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_IsStunned.generated.h"

/**
 * 
 */
UCLASS()
class SONDER_API UBTService_IsStunned : public UBTService_BlackboardBase
{
	GENERATED_BODY()
public:
	
	UBTService_IsStunned();

	/** I have no idea when this is called but it is needed as well */
	virtual void OnGameplayTaskDeactivated(UGameplayTask& Task) override;
	
protected:
	/** Tick node is called every tick service is in progress*/
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(VisibleAnywhere)
	class AEnemyCharacter* OwnerCharacter = nullptr;

	UPROPERTY(EditAnywhere)
	bool bDebug = false;

	void StopRepositioning();

	UPROPERTY()
	UBehaviorTreeComponent* TreeComponent;
	FTimerHandle StopRepositioningTimerHandle;
	
};
