// Fill out your copyright notice in the Description page of Project Settings.

#include "ZombieHomeInvasion.h"
#include "ZombieGameModeBase.h"
#include "ZombieWindow.h"


AZombieGameModeBase::AZombieGameModeBase()
	: Super()
{
	// set default pawn class to our Blueprinted character
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	//DefaultPawnClass = PlayerPawnClassFinder.Class;

	bZombieWindowsDestroyed = false;
}

void AZombieGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!bGameIsOver)
	{
		Time += DeltaTime;
	}
}


void AZombieGameModeBase::SetGameOver(bool bGameOver)
{
	if (bGameOver)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Game Over! You survived seconds."), Time));
	}
	else // reset game
	{
		Time = 0;
	}
	// iterate through actors, all the zombie windows in the world
	for (TActorIterator<AZombieWindow> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		ActorItr->SetHealth(100); // reset all windows health
	}

	bGameIsOver = bGameOver;
}

void AZombieGameModeBase::SetZombieWindowDeath(bool ZombieWindowStatus)
{
	bZombieWindowsDestroyed = ZombieWindowStatus;
}

bool AZombieGameModeBase::GetZombieWindowDeath()
{
	return bZombieWindowsDestroyed;
}

bool AZombieGameModeBase::GetGameIsOver()
{
	return bGameIsOver;
}

float AZombieGameModeBase::GetGameTime()
{
	return Time;
}

FString AZombieGameModeBase::ConvertTime()
{
	int32 IntTime = (int32)Time;
	int32 minute = (IntTime % 3600) / 60;  // Minute component
	int32 seconds = IntTime % 60; // Second component

	FString minuteString = FString::FromInt(minute);
	FString secondString = FString::FromInt(seconds);

	FString finalString = minuteString + ":" + secondString;
	return finalString;
}







