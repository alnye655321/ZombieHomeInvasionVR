// Fill out your copyright notice in the Description page of Project Settings.

#include "ZombieHomeInvasion.h"
#include "Crowbar.h"
#include "Board.h"


// Sets default values
ACrowbar::ACrowbar()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CrowbarRoot = CreateDefaultSubobject <USceneComponent>(TEXT("CrowbarRoot"));
	RootComponent = CrowbarRoot;

	CrowbarMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CrowbarMesh"));
	CrowbarMesh->AttachToComponent(CrowbarRoot, FAttachmentTransformRules::SnapToTargetNotIncludingScale); // attach to root

	CrowbarMesh->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));
	CrowbarMesh->bGenerateOverlapEvents = true; // turn on overlap

	CrowbarMesh->OnComponentHit.AddDynamic(this, &ACrowbar::OnHit);

}

// Called when the game starts or when spawned
void ACrowbar::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACrowbar::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	ABoard* PotentialBoard = Cast<ABoard>(OtherActor);

	if (PotentialBoard != NULL) // crowbar hits a board
	{
		PotentialBoard->MoveBoard(); // release the board, sim physics
	}

}



