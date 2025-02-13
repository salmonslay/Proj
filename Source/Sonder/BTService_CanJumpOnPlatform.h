// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_CanJumpOnPlatform.generated.h"

class AShadowCharacter;
/**
 * 
 */
UCLASS()
class SONDER_API UBTService_CanJumpOnPlatform : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:

	UBTService_CanJumpOnPlatform();

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	
	UPROPERTY()
	AShadowCharacter* OwnerCharacter = nullptr;

	UPROPERTY()
	FVector OwnerLocation = FVector::ZeroVector;

	UPROPERTY(EditAnywhere)
	float JumpBoost = 10.f;
	
	UPROPERTY(EditAnywhere)
	bool bDebug = false;

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector BBKeyIsJumping;

	UPROPERTY()
	UBlackboardComponent* BlackboardComponent;

};
