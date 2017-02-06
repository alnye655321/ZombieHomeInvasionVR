// Fill out your copyright notice in the Description page of Project Settings.

#include "ZombieHomeInvasion.h"
#include "Hammer.h"


// Sets default values
AHammer::AHammer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	HammerRoot = CreateDefaultSubobject <USceneComponent>(TEXT("HammerRoot"));
	RootComponent = HammerRoot;

	HammerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HammerMesh"));
	HammerMesh->AttachToComponent(HammerRoot, FAttachmentTransformRules::SnapToTargetNotIncludingScale); // attach to root

	HammerMesh->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));
	HammerMesh->SetSimulatePhysics(true);
	HammerMesh->SetNotifyRigidBodyCollision(true); // should enable hit events
	HammerMesh->bGenerateOverlapEvents = true; // turn on overlap
	HammerMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

}

// Called when the game starts or when spawned
void AHammer::BeginPlay()
{
	Super::BeginPlay();
	
}


