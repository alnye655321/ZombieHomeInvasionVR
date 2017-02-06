// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Hammer.generated.h"

UCLASS()
class ZOMBIEHOMEINVASION_API AHammer : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHammer();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//root component for hammer
	UPROPERTY(EditAnywhere)
		USceneComponent* HammerRoot;

	//mesh for the hammer
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* HammerMesh;

	
	
};
