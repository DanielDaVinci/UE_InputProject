// Input game. All Rights Reserved.


#include "Traps/TrampolineTrap.h"
#include "MainCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void ATrampolineTrap::SetScaleByPercent(float PercentProgress)
{
	const FVector NewScale = (EndScale - FVector::OneVector) * PercentProgress + FVector::OneVector;
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
		
		Character->GetCharacterMovement()->Velocity *= XYLaunchBraking;
		FVector LaunchVelocity(0.0f, 0.0f, ZLaunchVelocity);
		Character->LaunchCharacter(LaunchVelocity, false, true);
	}
}
