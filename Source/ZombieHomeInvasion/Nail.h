// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Nail.generated.h"

UCLASS()
class ZOMBIEHOMEINVASION_API ANail : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANail();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//root component for board
	UPROPERTY(EditAnywhere)
		USceneComponent* NailRoot;

	//mesh for the board
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* NailMesh;

	UFUNCTION()
		bool GetOnBoard();

	UFUNCTION()
		void SetOnBoard(bool OnBoard);

	// controls hammer hitting nail
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);


private:
	bool bOnBoard;
	uint16 NailHammerHitCount;
	
	TArray<AActor*> arrOverlappedActors;
	
};
