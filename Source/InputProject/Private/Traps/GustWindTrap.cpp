// Input game. All Rights Reserved.


#include "Traps/GustWindTrap.h"

AGustWindTrap::AGustWindTrap()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AGustWindTrap::ChangeRandomWindDirection()
{
	m_currentWindDirection = FVector2D(FMath::RandRange(-1.0f, 1.0f), FMath::RandRange(-1.0f, 1.0f)).GetSafeNormal();
}

void AGustWindTrap::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(m_directionChangeTimer, this, &AGustWindTrap::ChangeRandomWindDirection,
	                                m_windChangeFrequency, true, 0.0f);
}

void AGustWindTrap::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	m_trappedActors.Add(OtherActor);
	PrimaryActorTick.bCanEverTick = true;
}

void AGustWindTrap::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);

	if (m_trappedActors.Num() == 1)
		PrimaryActorTick.bCanEverTick = false;
	m_trappedActors.Remove(OtherActor);
}

void AGustWindTrap::MoveTrappedActors(float DeltaTime)
{
	for (int32 i = 0; i < m_trappedActors.Num(); i++)
	{
		AActor* Actor = m_trappedActors[i];
		
		FVector WindShift = GetActorRotation().RotateVector(FVector(m_currentWindDirection, 0.0f)) * m_windForce * DeltaTime;
		FVector NewActorLocation = Actor->GetActorLocation() + WindShift;
		
		Actor->SetActorLocation(NewActorLocation);
	}
}

void AGustWindTrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MoveTrappedActors(DeltaTime);
}
