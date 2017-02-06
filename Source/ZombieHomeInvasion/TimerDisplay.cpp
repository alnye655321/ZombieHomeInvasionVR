// Fill out your copyright notice in the Description page of Project Settings.

#include "ZombieHomeInvasion.h"
#include "TimerDisplay.h"
#include "ZombieGameModeBase.h"


// Sets default values
ATimerDisplay::ATimerDisplay()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TimerRoot = CreateDefaultSubobject <USceneComponent>(TEXT("TimerRoot"));
	RootComponent = TimerRoot;

	TimerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TimerMesh"));
	TimerMesh->AttachToComponent(TimerRoot, FAttachmentTransformRules::SnapToTargetNotIncludingScale); // attach to root

	TimerMesh->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));
	TimerMesh->bGenerateOverlapEvents = true; // turn on overlap

	TimerText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TimerText"));
	TimerText->AttachToComponent(TimerRoot, FAttachmentTransformRules::SnapToTargetNotIncludingScale); // attach to root
}

// Called when the game starts or when spawned
void ATimerDisplay::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATimerDisplay::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	AZombieGameModeBase* GameMode = (AZombieGameModeBase*)GetWorld()->GetAuthGameMode(); // get ref to game mode
	FString TimeFromGameMode = GameMode->ConvertTime(); // run time conversion in game mode
	TimerText->SetText(TimeFromGameMode); // update the timer display

}

