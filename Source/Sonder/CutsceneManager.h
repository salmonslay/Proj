// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SonderSaveGame.h"
#include "Engine/TriggerBox.h"
#include "CutsceneManager.generated.h"

class UInputMappingContext;
/**
 * Cutscene class handling playing all cutscenes 
 */
UCLASS()
class SONDER_API ACutsceneManager : public ATriggerBox
{
	GENERATED_BODY()

public:

	ACutsceneManager(); 

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	static bool IsCutscenePlaying() { return CutscenesPlayingCounter != 0; }

	/** Call to play the assigned cutscene for all players */
	UFUNCTION(Server, Reliable, BlueprintCallable)
	void ServerRPC_PlayCutscene();

	UDELEGATE()
	DECLARE_DYNAMIC_MULTICAST_DELEGATE( FCutsceneFinishedDelegate ); 

	/** Delegate called when cutscene ends */
	UPROPERTY(BlueprintAssignable)
	FCutsceneFinishedDelegate CutsceneFinishedDelegate; 

protected:

	// local player controllers, 1 when playing online. 2 local 
	UPROPERTY(BlueprintReadOnly)
	TArray<APlayerController*> PlayerControllers;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bDisplayWidgetOnCutsceneEnd = true; 
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnCutsceneEnd(const bool bLoadingNewMap);

	UFUNCTION(BlueprintImplementableEvent)
	void OnCutsceneSkipped();

private:

	/** Auto plays the cutscene on level load */
	UPROPERTY(EditAnywhere)
	bool bAutoPlay = false;

	/** How long to wait before playing the cutscene when auto play is active. Should match the fade in time.
	 *  Needed so both players have time to load in. */ 
	UPROPERTY(EditAnywhere)
	float AutoPlayDelayTime = 1.5f; 

	/** Plays the cutscene when any player overlaps with it */
	UPROPERTY(EditAnywhere)
	bool bPlayOnOverlap = false; 

	/** Input action for skipping the cutscene */
	UPROPERTY(EditDefaultsOnly)
	class UInputAction* SkipInputAction;

	/** The default input action mapping used for the players */
	UPROPERTY(EditDefaultsOnly)
	UInputMappingContext* DefaultInputMap;

	/** The input action mapping to use during cutscenes */
	UPROPERTY(EditDefaultsOnly)
	UInputMappingContext* CutsceneInputMap; 

	/** The sequence player, plays the assigned Sequencer */
	UPROPERTY()
	class ULevelSequencePlayer* LevelSequencePlayer;

	/** The level sequence to play / the cutscene */
	UPROPERTY(EditAnywhere)
	class ULevelSequence* Sequencer;

	/** Keeps track of how many cutscenes are playing to account for multiple players */
	inline static int CutscenesPlayingCounter = 0;

	bool bHasPlayed = false;

	bool bHasStopped = false; 

	/** Should players be hidden during cutscene? */
	UPROPERTY(EditAnywhere)
	bool bHidePlayersDuringCutscene = true;
    
	/** The level to load when the cutscene finished playing. Leaving it empty loads no new level
     *  NOTE: Needs to be in form of: Levels/MAPNAMEGOESHERE or just the map name if in the Maps folder */ 
	UPROPERTY(EditAnywhere)
	FName LevelToLoadOnCutsceneEnd = NAME_None;

	/** Widget shown until the cutscene starts playing, probably a black screen but not necessarily.
	 * Is removed when cutscene starts */
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> AutoPlayBlackScreenWidget;

	/** The widget created which will be removed when cutscene starts */
	UPROPERTY()
	class UUserWidget* AutoPlayWidget;

	/** Stores the widgets that were hidden when cutscene began */
	TArray<UUserWidget*> WidgetsHidden;

	/** Widget classes to hide during cutscenes */
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> WidgetsToHide;

	inline static FString LatestPlayedCutsceneLevel = "";

	UPROPERTY(EditAnywhere)
	ESonderLevel LevelToMarkAsCompleted = ESonderLevel::None; 

	/** Plays the assigned cutscene */
	void PlayCutscene();

	UFUNCTION(NetMulticast, Reliable)
	void MulticastRPC_PlayCutscene(); 

	/** Switches the player's input map to the cutscene's so input is disabled except for skip cutscene */
	void DisablePlayerInput() const;

	/** Switches the player's input map to the default input */
	void EnablePlayerInput() const;

	void BindSkipCutsceneButton(); 

	/** Removes the HUD for the player */
	void RemoveHUD();

	void ShowHud(); 
	
	/** Stops the cutscene and resets everything. Called either by skipping or when cutscene finished naturally */
	void StopCutscene();

	UFUNCTION(Server, Reliable)
	void ServerRPC_StopCutscene();

	UFUNCTION(NetMulticast, Reliable)
	void MulticastRPC_StopCutscene();

	/** Sets players' visibility */ 
	void TogglePlayerVisibility(const bool bVisible) const; 
	
};
