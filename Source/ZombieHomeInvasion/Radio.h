// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Radio.generated.h"

UCLASS()
class ZOMBIEHOMEINVASION_API ARadio : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARadio();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//root component for board
	UPROPERTY(EditAnywhere)
		USceneComponent* RadioRoot;

	//mesh for the board
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* RadioMesh;
	

private:
	
	bool PlayerPickedUp;
	
	void BeepMe();

	FTimerHandle RadioTimerHandle;

	FTimerHandle BeginPlayTimerHandle;

	USoundCue* beepAudioCue;
	UAudioComponent* beepAudioComponent;
	
};
