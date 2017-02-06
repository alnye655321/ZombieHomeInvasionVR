// Fill out your copyright notice in the Description page of Project Settings.

#include "ZombieHomeInvasion.h"
#include "Torch.h"
#include "Lighter.h"


// Sets default values
ATorch::ATorch()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	TorchRoot = CreateDefaultSubobject <USceneComponent>(TEXT("TorchRoot"));
	RootComponent = TorchRoot;

	TorchMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TorchMesh"));
	TorchMesh->AttachToComponent(TorchRoot, FAttachmentTransformRules::SnapToTargetNotIncludingScale); // attach to root

	TorchMesh->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));
	TorchMesh->SetSimulatePhysics(true);
	TorchMesh->bGenerateOverlapEvents = true; // turn on overlap
	TorchMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	// load audio cue - fire crackle
	static ConstructorHelpers::FObjectFinder<USoundCue>torchAudioCueRef(TEXT("'/Game/Sounds/Torch/fire_crackle_cue.fire_crackle_cue'"));

	torchAudioCue = torchAudioCueRef.Object; // reference to the Cue asset	

	torchAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("BeepAudioComp")); // Create an audio component, and wrap the Cue

	// don't play the moment it's created.
	torchAudioComponent->bAutoActivate = false;

	// attach to root of radio
	torchAudioComponent->AttachToComponent(TorchRoot, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	// set location relative to the radio - slightly in front
	torchAudioComponent->SetRelativeLocation(FVector(100.0f, 0.0f, 0.0f));

	// set parameter of the sound cue during runtime
	//beepAudioComponent->SetFloatParameter(FName("pitch"), 2500.f);

	// close fire crackle

}

// Called when the game starts or when spawned
void ATorch::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATorch::LightItUp(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{
	ALighter* PotentialLighter = Cast<ALighter>(OtherActor);

	if (PotentialLighter != NULL) // play the fire sound - will spawn an emitter in engine
	{
		// attach sound cue to the SoundComponent
		if (torchAudioCue->IsValidLowLevelFast()) {
			torchAudioComponent->SetSound(torchAudioCue);
		}

		// play fire crackle cue
		torchAudioComponent->Play();
	}
}


