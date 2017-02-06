// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameModeBase.h"
#include "ZombieGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class ZOMBIEHOMEINVASION_API AZombieGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AZombieGameModeBase();

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Game State")
		void SetGameOver(bool bGameOver); // function to end the game, can be called in blueprints

	// state of zombie windows
	UFUNCTION(BlueprintCallable, Category = "Game State")
		void SetZombieWindowDeath(bool ZombieWindowStatus);

	UFUNCTION(BlueprintCallable, Category = "Game State")
		bool GetZombieWindowDeath();


	bool GetGameIsOver(); // check if game is over

	float Time = 0.f;

	UFUNCTION()
		float GetGameTime();

	FString ConvertTime();



	
private:

	int32 Score = 0;



	int32 TargetsShot = 0;

	int32 PointsToFinish = 0;

	bool bGameIsOver = true; // default game is over, until player starts it

	bool bZombieWindowsDestroyed; // used to trigger zombies seeking player
};
