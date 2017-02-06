// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Crowbar.generated.h"

UCLASS()
class ZOMBIEHOMEINVASION_API ACrowbar : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACrowbar();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	//root component for crowbar
	UPROPERTY(EditAnywhere)
		USceneComponent* CrowbarRoot;

	//mesh for the crowbar
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* CrowbarMesh;

	// controls crowbar hitting board
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
	
};
