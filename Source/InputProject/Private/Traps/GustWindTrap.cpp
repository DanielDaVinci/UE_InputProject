// Input game. All Rights Reserved.


#include "Traps/GustWindTrap.h"

AGustWindTrap::AGustWindTrap()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AGustWindTrap::ChangeRandomWindDirection()
{
	CurrentWindDirection = FVector2D(FMath::RandRange(-1.0f, 1.0f), FMath::RandRange(-1.0f, 1.0f)).GetSafeNormal();
}

void AGustWindTrap::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(DirectionChangeTimer, this, &AGustWindTrap::ChangeRandomWindDirection,
	                                WindChangeFrequency, true, 0.0f);
}

void AGustWindTrap::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	TrappedActors.Add(OtherActor);
	PrimaryActorTick.bCanEverTick = true;
}

void AGustWindTrap::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);

	if (TrappedActors.Num() == 1)
		PrimaryActorTick.bCanEverTick = false;
	TrappedActors.Remove(OtherActor);
}

void AGustWindTrap::MoveTrappedActors(float DeltaTime)
{
	for (int32 i = 0; i < TrappedActors.Num(); i++)
	{
		AActor* Actor = TrappedActors[i];
		
		FVector WindShift = GetActorRotation().RotateVector(FVector(CurrentWindDirection, 0.0f)) * WindForce * DeltaTime;
		FVector NewActorLocation = Actor->GetActorLocation() + WindShift;
		
		Actor->SetActorLocation(NewActorLocation);
	}
}

void AGustWindTrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MoveTrappedActors(DeltaTime);
}
