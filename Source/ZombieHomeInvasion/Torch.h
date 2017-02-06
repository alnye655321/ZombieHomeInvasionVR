// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Torch.generated.h"

UCLASS()
class ZOMBIEHOMEINVASION_API ATorch : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATorch();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	//root component for torch
	UPROPERTY(EditAnywhere)
		USceneComponent* TorchRoot;

	//mesh for the torch
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* TorchMesh;

	// controls lighter hitting torch
	UFUNCTION()
		void LightItUp(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
	
private:
	USoundCue* torchAudioCue;
	UAudioComponent* torchAudioComponent;
	
};
