// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/BlueprintFunctionLibrary.h" //!!! Needed for blueprint function call -- used in animation
#include "ZombieCharacter.generated.h"


UCLASS()
class ZOMBIEHOMEINVASION_API AZombieCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AZombieCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//root component for zombie
	UPROPERTY(EditAnywhere)
		USceneComponent* ZombieRoot;

	//movement component
	UPROPERTY(EditAnywhere)
		UMovementComponent* ZombieMovement;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* ZombieBodyMesh;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* ZombieHeadMesh;

	UPROPERTY(EditAnywhere)
		UCapsuleComponent* RightFist;

	UPROPERTY(EditAnywhere)
		UCapsuleComponent* LeftFist;

	UFUNCTION(BlueprintCallable, Category = "Zombie")
		FVector StanceAroundPlayer();

	UFUNCTION(BlueprintCallable, Category = "Zombie")
		int32 GetHealth();

	UFUNCTION(BlueprintCallable, Category = "Zombie")
		void SetHealth(int32 NewHealth);

	UFUNCTION(BlueprintCallable, Category = "Zombie")
		void SeekWindow();

	UFUNCTION(BlueprintCallable, Category = "Player")
		void SeekPlayer();

	UFUNCTION(BlueprintCallable, Category = "BP_Call")
		static void CallToBP(AActor * c);

	// called when a right fist makes contact with player
	UFUNCTION()
		void RightFistOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	// called when a left fist makes contact with player
	UFUNCTION()
		void LeftFistOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// called when a zombie overlaps a window - used to begin window attack
	UFUNCTION()
		void WindowOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// called when a zombie ends overlaping a window - used to end window attack
	UFUNCTION()
		void EndWindowOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	// called when a zombie an object overlaps zombie head - used to deal damage to zombie
	UFUNCTION()
		void HeadOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	float Speed;
	float Distance;	
	float DistanceWindow;
	float DistancePlayer;
	int32 Health;
	int32 WindowArrayValue;
	bool bAlive;
	bool bIsAttacking;
	bool bIsMovingToWindow;
	bool bIsWindowAttacking;
	bool bWindowsDestroyed;
	FVector vWindowLocation;
	FVector vPlayerStanceLocation;

	TArray<AActor*> FoundWindows;
	TArray<AActor*> RightFistOverlappedActors;
	TArray<AActor*> LeftFistOverlappedActors;

	
	FTimerHandle DistanceTimerHandle;
	FTimerHandle WindowAttackTimerHandle;
	FTimerHandle WindowStatusTimerHandle;

	void PlayerDistance();
	void AttackCloseRange();
	void FacePlayer();
	void WindowAttack();
	void WindowsDestroyedCheck();
};
