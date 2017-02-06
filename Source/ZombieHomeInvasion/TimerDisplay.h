// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "TimerDisplay.generated.h"

UCLASS()
class ZOMBIEHOMEINVASION_API ATimerDisplay : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATimerDisplay();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	//root component for timer
	UPROPERTY(EditAnywhere)
		USceneComponent* TimerRoot;

	//mesh for the timer
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* TimerMesh;

	UPROPERTY(EditAnywhere)
		UTextRenderComponent* TimerText;

	
};
