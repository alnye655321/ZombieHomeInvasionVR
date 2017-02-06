// Fill out your copyright notice in the Description page of Project Settings.

#include "ZombieHomeInvasion.h"
#include "PlayerCharacter.h"
#include "ZombieCharacter.h"
#include "ZombieGameModeBase.h"


// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Health = 100;

	PlayerRoot = CreateDefaultSubobject <USceneComponent>(TEXT("PlayerRoot"));
	RootComponent = PlayerRoot;

	PlayerBodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlayerBodyMesh")); // create plyaer body for world collisions
	PlayerBodyMesh->AttachToComponent(PlayerRoot, FAttachmentTransformRules::SnapToTargetNotIncludingScale); // attach to root
	PlayerBodyMesh->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));
	PlayerBodyMesh->bGenerateOverlapEvents = true; //define collisions
	PlayerBodyMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	PlayerBodyMesh->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacter::ZombieOverlap); // add overlap event for a zombie body attack
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APlayerCharacter::ZombieOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	AZombieCharacter* PotentialZombie = Cast<AZombieCharacter>(OtherActor);

	if (PotentialZombie != NULL)
	{
		this->SetHealth(Health - 10); // take 10 damage from successful zombie hit
	}
}

void APlayerCharacter::SetHealth(int32 NewHealth)
{
	Health = NewHealth;

	if (Health <= 0)
	{
		AZombieGameModeBase* GameMode = (AZombieGameModeBase*)GetWorld()->GetAuthGameMode(); // get ref to game mode
		GameMode->SetGameOver(true); // end the game on player death
	}
}

int32 APlayerCharacter::GetHealth()
{
	return Health;
}

