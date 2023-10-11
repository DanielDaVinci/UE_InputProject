// Input game. All Rights Reserved.


#include "Traps/DisappearTrap.h"

void ADisappearTrap::StartShakeAnimation()
{
	GetWorldTimerManager().SetTimer(ShakeTimer, this, &ADisappearTrap::Shake, ShakingFrequency, true, 0.0f);
	GetWorldTimerManager().SetTimer(AnimationTimer, this, &ADisappearTrap::OnEndAnimation, AnimationTime, false);
}

void ADisappearTrap::Shake()
{
	FVector ShakeShift = FMath::VRand() * ShakingAmplitude;
	UE_LOG(LogTemp, Display, TEXT("%s"), *ShakeShift.ToString());
	SetActorLocation(GetActorLocation() - CurrentShakeShift + ShakeShift);

	CurrentShakeShift = ShakeShift;
}

void ADisappearTrap::OnEndAnimation()
{
	GetWorldTimerManager().ClearTimer(ShakeTimer);
	Destroy();
}

void ADisappearTrap::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	
	if (!AnimationTimer.IsValid())
		StartShakeAnimation();
}
