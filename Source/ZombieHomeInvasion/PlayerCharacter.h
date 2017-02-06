// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class ZOMBIEHOMEINVASION_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// mesh components for player
	UPROPERTY(EditAnywhere)
		USceneComponent* PlayerRoot;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* PlayerBodyMesh;

	// called when a zombie lands an attack on player
	UFUNCTION()
		void ZombieOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void SetHealth(int32 NewHealth);

	int32 GetHealth();

private:
	int32 Health;
	
};
