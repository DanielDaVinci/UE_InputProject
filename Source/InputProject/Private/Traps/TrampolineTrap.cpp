// Input game. All Rights Reserved.


#include "Traps/TrampolineTrap.h"
#include "MainCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void ATrampolineTrap::SetScaleByPercent(float PercentProgress)
{
	const FVector NewScale = (m_endScale - FVector::OneVector) * PercentProgress + FVector::OneVector;
	SetActorScale3D(NewScale);
}

void ATrampolineTrap::Launch()
{
	TArray<AActor*> OverlapActors;
	GetOverlappingActors(OverlapActors, AMainCharacter::StaticClass());
	
	for (AActor* Actor : OverlapActors)
	{
		AMainCharacter* Character = Cast<AMainCharacter>(Actor);
		if (!Character)
			continue;
		
		Character->GetCharacterMovement()->Velocity *= m_xyLaunchBraking;
		FVector LaunchVelocity(0.0f, 0.0f, m_zLaunchVelocity);
		Character->LaunchCharacter(LaunchVelocity, false, true);
	}
}
