// Fill out your copyright notice in the Description page of Project Settings.

#include "ZombieHomeInvasion.h"
#include "Kismet/KismetMathLibrary.h"
#include "PlayerCharacter.h"
#include "ZombieWindow.h"
#include "ZombieCharacter.h"
#include "ZombieGameModeBase.h"


// Sets default values
AZombieCharacter::AZombieCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bIsAttacking = false;
	bIsWindowAttacking = false;
	Health = 100;
	bAlive = true;
	bWindowsDestroyed = false;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AZombieWindow::StaticClass(), FoundWindows); // set FoundWindows array with all window actors

	WindowArrayValue = FMath::RandRange(0, 2); // assign to one of three possible windows

	ZombieRoot = CreateDefaultSubobject <USceneComponent>(TEXT("ZombieRoot"));
	RootComponent = ZombieRoot;

	ZombieMovement = CreateDefaultSubobject<UMovementComponent>(TEXT("ZombieMovement"));

	ZombieBodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ZombieBody")); // create zombie body for world collisions
	ZombieBodyMesh->AttachToComponent(ZombieRoot, FAttachmentTransformRules::SnapToTargetNotIncludingScale); // attach to root
	ZombieBodyMesh->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));
	ZombieBodyMesh->bGenerateOverlapEvents = true; //define collisions
	ZombieBodyMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	ZombieBodyMesh->OnComponentBeginOverlap.AddDynamic(this, &AZombieCharacter::WindowOverlap); // add overlap event for window, will begin window attack
	ZombieBodyMesh->OnComponentEndOverlap.AddDynamic(this, &AZombieCharacter::EndWindowOverlap); // end overlap and stop attack

	ZombieHeadMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ZombieHead")); // zombie head - used for damage - only head shots allowed
	ZombieHeadMesh->AttachToComponent(ZombieRoot, FAttachmentTransformRules::SnapToTargetNotIncludingScale); // attach to root
	ZombieHeadMesh->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));
	ZombieHeadMesh->bGenerateOverlapEvents = true; //define collisions
	ZombieHeadMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	ZombieHeadMesh->OnComponentBeginOverlap.AddDynamic(this, &AZombieCharacter::HeadOverlap); // add overlap event for window, will begin window attack

	RightFist = CreateDefaultSubobject<UCapsuleComponent>(TEXT("RightFist"));
	RightFist->AttachToComponent(ZombieRoot, FAttachmentTransformRules::SnapToTargetNotIncludingScale); // attach to root
	RightFist->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));
	RightFist->bGenerateOverlapEvents = true; // turn on overlap
	RightFist->SetCollisionEnabled(ECollisionEnabled::NoCollision); // turn off collision by default, enabled when attacked
	RightFist->OnComponentBeginOverlap.AddDynamic(this, &AZombieCharacter::RightFistOverlap); // add overlap events

	LeftFist = CreateDefaultSubobject<UCapsuleComponent>(TEXT("LeftFist"));	
	LeftFist->AttachToComponent(ZombieRoot, FAttachmentTransformRules::SnapToTargetNotIncludingScale);		
	LeftFist->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));
	LeftFist->bGenerateOverlapEvents = true;
	LeftFist->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	LeftFist->OnComponentBeginOverlap.AddDynamic(this, &AZombieCharacter::LeftFistOverlap);

}

// Called when the game starts or when spawned
void AZombieCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// looping - keep track of distance from player - every second
	GetWorldTimerManager().SetTimer(DistanceTimerHandle, this, &AZombieCharacter::PlayerDistance, 1.0f, true);

	// looping - keep track window health status - every 3 seconds
	GetWorldTimerManager().SetTimer(WindowStatusTimerHandle, this, &AZombieCharacter::WindowsDestroyedCheck, 3.0f, true);

	SeekWindow(); // begin life by seeking a window
}

// Called every frame
void AZombieCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void AZombieCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

//-------------------------------------- Zombie Actions ---------------------------------------------------------

// blueprint engine call for animation
void AZombieCharacter::CallToBP(AActor * c)
{
	FOutputDeviceNull ar;
	c->CallFunctionByNameWithArguments(TEXT("CallAttackAnimation"), ar, NULL, true); // text is blueprint function name
}

int32 AZombieCharacter::GetHealth()
{
	return Health;
}

void AZombieCharacter::SetHealth(int32 NewHealth)
{
	Health = NewHealth;

	if (Health <= 0)
	{
		// clear all timers
		GetWorld()->GetTimerManager().ClearAllTimersForObject(this);

		// destroy actor
		Destroy();
	}
}

// called when a zombie an object overlaps zombie head - used to deal damage to zombie
void AZombieCharacter::HeadOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	this->SetHealth(Health - 1); // take 1 damage to health from any overlapping object, weapons etc.
}

// ------------------------------------- Window Actions -------------------------------------------------------

void AZombieCharacter::WindowsDestroyedCheck()
{
	// check with game mode
	AZombieGameModeBase* GameMode = (AZombieGameModeBase*)GetWorld()->GetAuthGameMode(); // get ref to game mode
	bool ZombieWindowDestroyed = GameMode->GetZombieWindowDeath();
	
	if (ZombieWindowDestroyed)
	{
		bWindowsDestroyed = true;
	}
}

// pathfinding to assigned window
void AZombieCharacter::SeekWindow()
{
	if (bIsAttacking)
	{
		ZombieMovement->StopMovementImmediately();
	}
	else
	{
		FVector Destination;
		Destination = FoundWindows[WindowArrayValue]->GetActorLocation();
		// call AI move in engine and play sound
	}
}

void AZombieCharacter::WindowAttack()
{
	if (bWindowsDestroyed = true && bIsWindowAttacking) // windows are destroyed, stop attacked and seek player
	{
		bIsWindowAttacking = false;
		SeekPlayer();
	}
	else
	{
		FacePlayer();
		bIsAttacking = true;
		// window attack sequence
		// enable fist collisions
		LeftFist->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		RightFist->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

		CallToBP(this); // attack animation in engine

		// disable fist collisions
		LeftFist->SetCollisionEnabled(ECollisionEnabled::NoCollision); // turn off collision by default, enabled when attacked
		RightFist->SetCollisionEnabled(ECollisionEnabled::NoCollision); // turn off collision by default, enabled when attacked

		bIsAttacking = false;
		// keep attacking window after a delay
		GetWorldTimerManager().SetTimer(WindowAttackTimerHandle, this, &AZombieCharacter::WindowAttack, 1.0f, false); // recursive call to WindowAttack
		WindowAttack(); // keep attacking window

	}
}


// initial overlap of window after finding through SeekWindow()
void AZombieCharacter::WindowOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	AZombieWindow* PotentialZombieWindow = Cast<AZombieWindow>(OtherActor);

	if (PotentialZombieWindow != NULL) // zombie is in the window vicinity
	{
		bIsWindowAttacking = true;
		WindowAttack();
	}
}

// end overlap and stop zombie window attack
void AZombieCharacter::EndWindowOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	AZombieWindow* PotentialZombieWindow = Cast<AZombieWindow>(OtherActor);

	if (PotentialZombieWindow != NULL) // zombie is outside the window vicinity
	{
		bIsWindowAttacking = false;
	}
}

// ----------------------------------------------- Player Actions -----------------------------------------------------

// offset the location around the player in circle radius
// 50% chance, default is right up to plyaer
FVector AZombieCharacter::StanceAroundPlayer()
{
	int32 randomInt = FMath::RandRange(0, 5);
	ACharacter* PlayerChar = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	FVector PlayerLocation = PlayerChar->GetActorLocation();
	FVector IntendedZombieLocation;
	FVector VectorOffset = FVector(0.0f, 0.0f, 0.0f);

	switch (randomInt) {
	case 0:
		VectorOffset.X = 18.62598f;
		VectorOffset.Y = 194.871201f;
		IntendedZombieLocation = UKismetMathLibrary::Subtract_VectorVector(PlayerLocation, VectorOffset);
		break;

	case 1:
		VectorOffset.X = 190.626007f;
		VectorOffset.Y = -5.12878f;
		IntendedZombieLocation = UKismetMathLibrary::Subtract_VectorVector(PlayerLocation, VectorOffset);
		break;

	case 2:
		VectorOffset.X = -13.374f;
		VectorOffset.Y = -232.128998f;
		IntendedZombieLocation = UKismetMathLibrary::Subtract_VectorVector(PlayerLocation, VectorOffset);
		break;

			   
	default: 
		IntendedZombieLocation = PlayerLocation;
	}

	return IntendedZombieLocation;
}


// pathfinding to attack player
void AZombieCharacter::SeekPlayer()
{
	if (bIsAttacking)
	{
		ZombieMovement->StopMovementImmediately();
	}
	else if(DistancePlayer < 250.0f)
	{
		AttackCloseRange();
	}
	else
	{
		// call AI move in engine --> call StanceAroundPlayer()
	}
}





// gets the distance from the zombie to the player
void AZombieCharacter::PlayerDistance()
{
	ACharacter* PlayerChar = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	FVector PlayerLocation = PlayerChar->GetActorLocation();
	FVector ZombieLocation = this->GetActorLocation();
	FVector VectorDiff  = FVector(0.0f, 0.0f, 0.0f);
	float VectorLength = 0.0f;

	VectorDiff = UKismetMathLibrary::Subtract_VectorVector(ZombieLocation, PlayerLocation);
	VectorLength = UKismetMathLibrary::VSize(VectorDiff);
	DistancePlayer = VectorLength;
}

void AZombieCharacter::AttackCloseRange()
{
	bIsAttacking = true;
	FacePlayer();

	// enable fist collisions
	LeftFist->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	RightFist->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	CallToBP(this); // attack animation in engine

	// disable fist collisions
	LeftFist->SetCollisionEnabled(ECollisionEnabled::NoCollision); // turn off collision by default, enabled when attacked
	RightFist->SetCollisionEnabled(ECollisionEnabled::NoCollision); // turn off collision by default, enabled when attacked

	bIsAttacking = false;
	SeekPlayer(); // seek player after an attack
}

void AZombieCharacter::RightFistOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	// get all overlapping actors of fist and look for players or windows during attack sequence
	RightFist->GetOverlappingActors(RightFistOverlappedActors);
	for (int32 i = 0; i < RightFistOverlappedActors.Num(); i++)
	{
		APlayerCharacter* PotentialPlayer = Cast<APlayerCharacter>(RightFistOverlappedActors[i]);

		if (PotentialPlayer != NULL) // fist hit
		{
			PotentialPlayer->SetHealth( (PotentialPlayer->GetHealth()) - 10  ); // decrease player health by 10 after hit
		}

		AZombieWindow* PotentialZombieWindow = Cast<AZombieWindow>(RightFistOverlappedActors[i]);

		if (PotentialZombieWindow != NULL) // fist hit
		{
			PotentialZombieWindow->SetHealth((PotentialZombieWindow->GetHealth()) - 10); // decrease window health by 10 after hit
		}
	}
}

void AZombieCharacter::LeftFistOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	// get all overlapping actors of fist and look for players or windows during attack sequence
	LeftFist->GetOverlappingActors(LeftFistOverlappedActors);
	for (int32 i = 0; i < LeftFistOverlappedActors.Num(); i++)
	{
		APlayerCharacter* PotentialPlayer = Cast<APlayerCharacter>(LeftFistOverlappedActors[i]);

		if (PotentialPlayer != NULL) // fist hit
		{
			PotentialPlayer->SetHealth((PotentialPlayer->GetHealth()) - 10); // decrease player health by 10 after hit
		}

		AZombieWindow* PotentialZombieWindow = Cast<AZombieWindow>(LeftFistOverlappedActors[i]);

		if (PotentialZombieWindow != NULL) // fist hit
		{
			PotentialZombieWindow->SetHealth((PotentialZombieWindow->GetHealth()) - 10); // decrease window health by 10 after hit
		}
	}
}



void AZombieCharacter::FacePlayer()
{
	ACharacter* PlayerChar = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	FVector PlayerLocation = PlayerChar->GetActorLocation();
	FVector ZombieLocation = this->GetActorLocation();

	FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(ZombieLocation, PlayerLocation);
	LookAtRotation.Pitch = LookAtRotation.Pitch + 20.0f; // increase pitch to look at player
	this->SetActorRotation(LookAtRotation); // set new zombie rotation
}




