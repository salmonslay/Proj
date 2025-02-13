// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BaseHealthComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SONDER_API UBaseHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	
	// Sets default values for this component's properties
	UBaseHealthComponent();

protected:
	
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Health, meta=(AllowPrivateAccess = true), SaveGame, ReplicatedUsing=OnRep_HealthChange)
	float CurrentHealth;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Health, meta=(AllowPrivateAccess = true), SaveGame, Replicated)
	float MaxHealth = 100;

public:

	/** Call when owner takes damage, returns the actual damage taken */
	virtual float TakeDamage(float DamageAmount);

	/** Called when damage taken was enough to reach health <= 0 */
	UFUNCTION(BlueprintCallable)
	virtual void IDied() {} 

	/** Returns true if owner is dead */
	UFUNCTION(BlueprintPure)
	bool IsDead() const;

	/** Returns health as its float value */
	UFUNCTION(BlueprintPure)
	float GetHealth() const;

	/** Returns health as a percentage 0-1 */
	UFUNCTION(BlueprintPure)
	float GetHealthPercent() const;

	/** Set new health to passed value, clamped between 0 and max health */
	UFUNCTION(BlueprintCallable)
	void SetHealth(float NewHealth);

	/** Sets maximum health for the owner */
	UFUNCTION()
	void SetMaxHealth(float NewMaxHealth);

	/** Sets current health to max health */
	UFUNCTION(BlueprintCallable)
	void RefillHealth();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	void OnRep_HealthChange();

	UFUNCTION()
	void HealthUpdate();
		
};
