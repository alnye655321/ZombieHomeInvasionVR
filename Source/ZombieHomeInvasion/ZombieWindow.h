// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ZombieWindow.generated.h"

UCLASS()
class ZOMBIEHOMEINVASION_API AZombieWindow : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AZombieWindow();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	//virtual void Tick( float DeltaSeconds ) override;

	//root component for board
	UPROPERTY(EditAnywhere)
		USceneComponent* ZombieWindowRoot;

	//mesh for the board
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* ZombieWindowMesh;

	// called when board is in window
	UFUNCTION()
		void BoardOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


	// called when board leaves the window
	UFUNCTION()
		void BoardGone(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
		uint16 GetBoardAmount();

	UFUNCTION()
		void SetBoardAmount(uint16 BoardAmount);

	UFUNCTION()
		uint16 GetNailCount();

	UFUNCTION()
		void SetNailCount(uint16 NailAmount);

	UFUNCTION()
		uint16 GetHealth();

	UFUNCTION()
		void SetHealth(uint16 HealthAmount);

	UFUNCTION()
		void WindowDestroyed();

private:
	uint16 Health;
	uint16 BoardCount;
	uint16 NailCount;

	TArray<AActor*> arrOverlappedActors;

	FTimerHandle WindowDestroyedTimerHandle;
	
};
