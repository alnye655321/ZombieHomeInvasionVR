// Fill out your copyright notice in the Description page of Project Settings.

#include "ZombieHomeInvasion.h"
#include "Lighter.h"


// Sets default values
ALighter::ALighter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	LighterRoot = CreateDefaultSubobject <USceneComponent>(TEXT("LighterRoot"));
	RootComponent = LighterRoot;

	LighterMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LighterMesh"));
	LighterMesh->AttachToComponent(LighterRoot, FAttachmentTransformRules::SnapToTargetNotIncludingScale); // attach to root

	LighterMesh->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));
	LighterMesh->SetSimulatePhysics(true);
	LighterMesh->bGenerateOverlapEvents = true; // turn on overlap
	LighterMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

// Called when the game starts or when spawned
void ALighter::BeginPlay()
{
	Super::BeginPlay();
	
}


