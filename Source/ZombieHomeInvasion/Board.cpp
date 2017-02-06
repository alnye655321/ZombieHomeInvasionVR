// Fill out your copyright notice in the Description page of Project Settings.

#include "ZombieHomeInvasion.h"
#include "Board.h"
#include "Nail.h"


// Sets default values
ABoard::ABoard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Health = 100;
	NailCount = 0;
	bInWindowBox = false;

	BoardRoot = CreateDefaultSubobject <USceneComponent>(TEXT("BoardRoot"));
	RootComponent = BoardRoot;

	BoardMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CubeMesh"));
	BoardMesh->AttachToComponent(BoardRoot, FAttachmentTransformRules::SnapToTargetNotIncludingScale); // attach to root

	BoardMesh->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));
	BoardMesh->bGenerateOverlapEvents = true; // turn on overlap

	BoardMesh->OnComponentBeginOverlap.AddDynamic(this, &ABoard::NailOverlap); // call function on overlap


}

// Called when the game starts or when spawned
void ABoard::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABoard::HitMe(uint16 Damage)
{
	Health = Health - Damage;

	// if health is 0 destroy the board
	if (Health <= 0)
	{
		Destroy();
	}
}

void ABoard::NailOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	// called when player places a nail on a board
	// get all overlapping actors of the board and look for nails
	BoardMesh->GetOverlappingActors(arrOverlappedActors);
	for (int32 i = 0; i < arrOverlappedActors.Num(); i++)
	{
		ANail* PotentialNail = Cast<ANail>(arrOverlappedActors[i]);

		if (PotentialNail != NULL && NailCount < 2) // only 2 nails per board
		{
			PotentialNail->SetOnBoard(true); // put nail on board
		}

	}
}

void ABoard::MoveBoard()
{
	BoardMesh->SetSimulatePhysics(true);
}

void ABoard::DropBoard()
{
	BoardMesh->SetSimulatePhysics(false);
}

uint16 ABoard::GetHealth()
{
	return Health;
}

void ABoard::SetHealth(uint16 HealthAmount)
{
	Health = HealthAmount;
}

uint16 ABoard::GetNails()
{
	return NailCount;
}

void ABoard::SetNails(uint16 NailsAmount)
{
	NailCount = NailsAmount;
}

bool ABoard::GetInWindow()
{
	return bInWindowBox;
}

void ABoard::SetInWindow(bool InWindow)
{
	bInWindowBox = InWindow;
}

