// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Lighter.generated.h"

UCLASS()
class ZOMBIEHOMEINVASION_API ALighter : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALighter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;	


	//root component for lighter
	UPROPERTY(EditAnywhere)
		USceneComponent* LighterRoot;

	//mesh for the lighter
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* LighterMesh;
	
};
