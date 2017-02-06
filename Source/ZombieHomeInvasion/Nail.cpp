// Fill out your copyright notice in the Description page of Project Settings.

#include "ZombieHomeInvasion.h"
#include "Nail.h"
#include "Hammer.h"
#include "ZombieWindow.h"


// Sets default values
ANail::ANail()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	bOnBoard = false;
	NailHammerHitCount = 0;

	NailRoot = CreateDefaultSubobject <USceneComponent>(TEXT("NailRoot"));
	RootComponent = NailRoot;

	NailMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("NailMesh"));
	NailMesh->AttachToComponent(NailRoot, FAttachmentTransformRules::SnapToTargetNotIncludingScale); // attach to root

	NailMesh->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));
	NailMesh->SetSimulatePhysics(true);
	NailMesh->SetNotifyRigidBodyCollision(true); // should enable hit events
	NailMesh->bGenerateOverlapEvents = true; // turn on overlap
	NailMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	
	NailMesh->OnComponentHit.AddDynamic(this, &ANail::OnHit);

}

// Called when the game starts or when spawned
void ANail::BeginPlay()
{
	Super::BeginPlay();
	
}

bool ANail::GetOnBoard()
{
	return bOnBoard;
}

void ANail::SetOnBoard(bool OnBoard)
{
	bOnBoard = OnBoard;

	if (bOnBoard) // keep nail in place on board
	{
		NailMesh->SetSimulatePhysics(false);
	}
	else
	{
		NailMesh->SetSimulatePhysics(true);
	}
}

void ANail::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	AHammer* PotentialHammer = Cast<AHammer>(OtherActor);

	if (PotentialHammer != NULL && bOnBoard == true)
	{
		NailHammerHitCount++;

		if (NailHammerHitCount < 25) // only allow 25 hits per nail
		{
			// look for the window the nail is in
			NailMesh->GetOverlappingActors(arrOverlappedActors);
			for (int32 i = 0; i < arrOverlappedActors.Num(); i++)
			{
				AZombieWindow* PotentialZombieWindow = Cast<AZombieWindow>(arrOverlappedActors[i]);

				if (PotentialZombieWindow != NULL)
				{
					uint16 ZombieWindowHealth = PotentialZombieWindow->GetHealth();
					PotentialZombieWindow->SetHealth(ZombieWindowHealth + 1); // buff window health after successful hammer hit
				}
			} // end for
		}
	}
}



