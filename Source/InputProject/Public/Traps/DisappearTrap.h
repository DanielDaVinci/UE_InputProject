// Input game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Traps/BaseTrap.h"
#include "DisappearTrap.generated.h"

UCLASS()
class INPUTPROJECT_API ADisappearTrap : public ABaseTrap
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation")
	float m_animationTime = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation")
	float m_shakingFrequency = 0.01f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation", meta=(ClampMin="0.0", ClampMax="10.0"))
	float m_shakingAmplitude = 2.0f;

	void StartShakeAnimation();

	void Shake();

	void OnEndAnimation();

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

private:
	FTimerHandle m_shakeTimer;
	FTimerHandle m_animationTimer;

	FVector m_currentShakeShift = {0.0f, 0.0f, 0.0f};
};
