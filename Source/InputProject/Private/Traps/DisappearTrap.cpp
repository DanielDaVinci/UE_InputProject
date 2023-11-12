// Input game. All Rights Reserved.


#include "Traps/DisappearTrap.h"

void ADisappearTrap::StartShakeAnimation()
{
	GetWorldTimerManager().SetTimer(m_shakeTimer, this, &ADisappearTrap::Shake, m_shakingFrequency, true, 0.0f);
	GetWorldTimerManager().SetTimer(m_animationTimer, this, &ADisappearTrap::OnEndAnimation, m_animationTime, false);
}

void ADisappearTrap::Shake()
{
	FVector ShakeShift = FMath::VRand() * m_shakingAmplitude;
	SetActorLocation(GetActorLocation() - m_currentShakeShift + ShakeShift);

	m_currentShakeShift = ShakeShift;
}

void ADisappearTrap::OnEndAnimation()
{
	GetWorldTimerManager().ClearTimer(m_shakeTimer);
	Destroy();
}

void ADisappearTrap::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	
	if (!m_animationTimer.IsValid())
		StartShakeAnimation();
}
