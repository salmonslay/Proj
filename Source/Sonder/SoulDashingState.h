// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerCharState.h"
#include "SoulDashingState.generated.h"

/**
 * Soul char enters this state when dashing 
 */
UCLASS()
class SONDER_API USoulDashingState : public UPlayerCharState
{
	GENERATED_BODY()

public:

	virtual void Enter() override;

	virtual void BeginPlay() override;

	virtual void Update(const float DeltaTime) override;

	virtual void Exit() override;

	float GetMaxDashDistance() const { return MaxDashDistance; }

private:

	UPROPERTY(EditAnywhere)
	float DashForce = 180000.f; 

	float TempTimer = 0;

	UPROPERTY(EditAnywhere)
	TEnumAsByte<ECollisionChannel> DashBarCollisionChannel;

	UPROPERTY(EditAnywhere)
	float MaxDashDistance = 250.f;

	FVector StartLoc;

	UPROPERTY()
	class URobotHookingState* HookState;

	UPROPERTY(EditAnywhere)
	float DashDamageAmount = 3.f;

	UPROPERTY()
	class UCharacterMovementComponent* MovementComponent;

	UPROPERTY()
	class UCapsuleComponent* CapsuleComponent;

	UPROPERTY()
	class AShadowSoulCharacter* ShadowOwner;

	UPROPERTY()
	class ASoulCharacter* PlayerOwner; 
	
	/** The impulse/force need to be applied on the server */
	UFUNCTION(Server, Reliable)
	void ServerRPCDash(const FVector DashDir); 

	UFUNCTION(NetMulticast, Reliable)
	void MulticastRPCDash();

	UFUNCTION(Server, Reliable)
	void ServerExit(const FVector InputVec);

	UFUNCTION(NetMulticast, Reliable)
	void MulticastExit(); 

	/** Cancels potential hook shot if Robot is shooting towards Soul */
	void CancelHookShot();

	UFUNCTION(Server, Reliable)
	void ServerRPC_CancelHookShot();

	UFUNCTION(Client, Reliable)
	void ClientRPC_CancelHookShot();

	/** The actual function that cancels the hook shot */ 
	void EndHookShot(); 

	UFUNCTION()
	void ActorOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult); 

	void DashOverlap(AActor* OtherActor); 
	
	UFUNCTION(Server, Reliable)
	void ServerRPC_DamageActor(AActor* ActorToDamage);

	UFUNCTION(Server, Reliable)
	void ServerRPC_RobotBuff(class URobotBaseState* RobotBaseState);
	
};
