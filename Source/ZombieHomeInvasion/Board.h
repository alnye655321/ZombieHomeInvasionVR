// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Board.generated.h"

UCLASS()
class ZOMBIEHOMEINVASION_API ABoard : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABoard();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//root component for board
	UPROPERTY(EditAnywhere)
		USceneComponent* BoardRoot;

	//mesh for the board
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* BoardMesh;


	UFUNCTION()
		void HitMe(uint16 Damage);

	// called when nail is in board
	UFUNCTION()
		void NailOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void MoveBoard();

	UFUNCTION()
		void DropBoard();

	UFUNCTION()
		uint16 GetHealth();

	UFUNCTION()
		void SetHealth(uint16 HealthAmount);

	UFUNCTION()
		uint16 GetNails();

	UFUNCTION()
		void SetNails(uint16 NailsAmount);

	UFUNCTION()
		bool GetInWindow();

	UFUNCTION()
		void SetInWindow(bool InWindow);


private:
	uint16 Health;
	uint16 NailCount;
	bool bInWindowBox;

	TArray<AActor*> arrOverlappedActors;
	
	
};
