// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UINavController.h"
#include "GameFramework/PlayerController.h"
#include "ProjPlayerController.generated.h"

/**
 * 
 */

class APROJCharacter;

UCLASS()
class SONDER_API AProjPlayerController : public AUINavController
{
	GENERATED_BODY()

public:
	
	UClass* GetControlledPawnClass() const { return UsedPawnClass; }

	void SetControlledPawnClass(const TSubclassOf<APawn> PawnClass) { UsedPawnClass = PawnClass; }
	
	UFUNCTION()
	void OnFinishSeamlessTravel();

protected:

	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void Tick(float DeltaSeconds) override;

	virtual void OnPossess(APawn* InPawn) override;
	
private:

	/** Finds the camera in the level and sets it as view target/the player's camera */
	void SetCamera();

	UPROPERTY()
	class ACharactersCamera* MainCam;

	inline static int PlayerCount = 0; 

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<APawn> RobotPawnClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<APawn> BlobPawnClass;
	
	TSubclassOf<APawn> UsedPawnClass;

	UPROPERTY()
	APROJCharacter* PlayerCharacter;

	UPROPERTY(VisibleAnywhere)
	AActor* playerSpawnPoint;
};
