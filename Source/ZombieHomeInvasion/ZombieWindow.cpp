// Fill out your copyright notice in the Description page of Project Settings.

#include "ZombieHomeInvasion.h"
#include "ZombieWindow.h"
#include "Board.h"
#include "Nail.h"
#include "ZombieCharacter.h"
#include "ZombieGameModeBase.h"


// Sets default values
AZombieWindow::AZombieWindow()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Health = 100;
	BoardCount = 0;
	NailCount = 0;

	ZombieWindowRoot = CreateDefaultSubobject <USceneComponent>(TEXT("ZombieWindowRoot"));
	RootComponent = ZombieWindowRoot;

	ZombieWindowMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ZombieWindowMesh"));
	ZombieWindowMesh->AttachToComponent(ZombieWindowRoot, FAttachmentTransformRules::SnapToTargetNotIncludingScale); // attach to root

	ZombieWindowMesh->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));
	ZombieWindowMesh->bGenerateOverlapEvents = true; // turn on overlap

	ZombieWindowMesh->OnComponentBeginOverlap.AddDynamic(this, &AZombieWindow::BoardOverlap); // call function on overlap
	ZombieWindowMesh->OnComponentEndOverlap.AddDynamic(this, &AZombieWindow::BoardGone); // board leaves window

}

// Called when the game starts or when spawned
void AZombieWindow::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(WindowDestroyedTimerHandle, this, &AZombieWindow::WindowDestroyed, 1.0f, true); // check if the window is destroyed, looping every second
}

void AZombieWindow::BoardOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	// called when player places a nail on a board
	// get all overlapping actors of the board and look for nails
	ZombieWindowMesh->GetOverlappingActors(arrOverlappedActors);
	for (int32 i = 0; i < arrOverlappedActors.Num(); i++)
	{
		ABoard* PotentialBoard = Cast<ABoard>(arrOverlappedActors[i]);

		if (PotentialBoard != NULL && BoardCount < 2) // only 2 boards per window
		{			
			BoardCount++; // increase the amount of boards in this window
		}
	}
}

void AZombieWindow::BoardGone(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	// recount number of boards in window
	uint32 tempBoardCount = 0;
	ZombieWindowMesh->GetOverlappingActors(arrOverlappedActors); 
	
	for (int32 i = 0; i < arrOverlappedActors.Num(); i++)
	{
		ABoard* PotentialBoard = Cast<ABoard>(arrOverlappedActors[i]);

		if (PotentialBoard != NULL) // only 2 boards per window
		{
			tempBoardCount++; // increase the amount of boards in this window
		}
	}

	if (tempBoardCount > 2) // only allow 2 boards per window
	{
		BoardCount = 2;
	}
	else
	{
		BoardCount = tempBoardCount; // update board count
	}	
}

uint16 AZombieWindow::GetBoardAmount()
{
	return BoardCount;
}

void AZombieWindow::SetBoardAmount(uint16 BoardAmount)
{
	BoardCount = BoardAmount;
}

uint16 AZombieWindow::GetNailCount()
{
	return NailCount;
}

void AZombieWindow::SetNailCount(uint16 NailAmount)
{
	NailCount = NailAmount;
}

uint16 AZombieWindow::GetHealth()
{
	return Health;
}

void AZombieWindow::SetHealth(uint16 HealthAmount)
{
	if (Health < 200) // 200 is the max health of window
	{
		Health = HealthAmount;
	}	
}

void AZombieWindow::WindowDestroyed()
{
	if (Health <= 0)
	{
		// destroy the window
		Destroy(); 

		// notify game mode
		AZombieGameModeBase* GameMode = (AZombieGameModeBase*)GetWorld()->GetAuthGameMode(); // get ref to game mode
		GameMode->SetZombieWindowDeath(false); // set the window status in game mode
	}
}

