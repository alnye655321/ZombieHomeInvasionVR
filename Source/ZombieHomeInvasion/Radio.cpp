// Fill out your copyright notice in the Description page of Project Settings.

#include "ZombieHomeInvasion.h"
#include "Radio.h"


// Sets default values
ARadio::ARadio()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	PlayerPickedUp = false;

	RadioRoot = CreateDefaultSubobject <USceneComponent>(TEXT("RadioRoot"));
	RootComponent = RadioRoot;

	RadioMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RadioMesh"));
	RadioMesh->AttachToComponent(RadioRoot, FAttachmentTransformRules::SnapToTargetNotIncludingScale); // attach to root

	RadioMesh->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));
	RadioMesh->bGenerateOverlapEvents = true; // turn on overlap
	

	// load audio cue - radio beeps
	static ConstructorHelpers::FObjectFinder<USoundCue> beepAudioCueRef(TEXT("'/Game/Sounds/Walkie/walkieBeep_Cue.walkieBeep_Cue'"));
	
	beepAudioCue = beepAudioCueRef.Object; // reference to the Cue asset	

	beepAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("BeepAudioComp")); // Create an audio component, and wrap the Cue

	// don't play the moment it's created.
	beepAudioComponent->bAutoActivate = false;
	
	// attach to root of radio
	beepAudioComponent->AttachToComponent(RadioRoot, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	
	// set location relative to the radio - slightly in front
	beepAudioComponent->SetRelativeLocation(FVector(100.0f, 0.0f, 0.0f));

	// set parameter of the sound cue during runtime
	//beepAudioComponent->SetFloatParameter(FName("pitch"), 2500.f);

	// close radio beeps

}

// Called when the game starts or when spawned
void ARadio::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(BeginPlayTimerHandle, this, &ARadio::BeepMe, 240.0f, false); // call BeepMe after play has begun for 240 seconds
}


void ARadio::BeepMe()
{
	if (PlayerPickedUp == false) // player hasn't picked up the radio yet
	{
		// attach sound cue to the SoundComponent
		if (beepAudioCue->IsValidLowLevelFast()) {
			beepAudioComponent->SetSound(beepAudioCue);
		}

		// play beep audio cue
		beepAudioComponent->Play();

		GetWorldTimerManager().SetTimer(RadioTimerHandle, this, &ARadio::BeepMe, 1.0f, false); // recursive call to BeepMe after 1 second, last bool can be true for looping
	}
	else // player has picked up the radio - zombie attack started
	{
		// clear all timers
		GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
	}

}



