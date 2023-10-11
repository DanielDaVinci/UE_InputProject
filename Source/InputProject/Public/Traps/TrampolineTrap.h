// Input game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Traps/BaseTrap.h"
#include "TrampolineTrap.generated.h"

/**
 * 
 */
UCLASS()
class INPUTPROJECT_API ATrampolineTrap : public ABaseTrap
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation")
	float AnimationTime = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation")
	FVector EndScale = {1.2f, 1.2f, 1.2f};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement")
	float ZLaunchVelocity = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement")
	float XYLaunchBraking = 0.1f;

	UFUNCTION(BlueprintCallable)
	void SetScaleByPercent(float PercentProgress);

	UFUNCTION(BlueprintCallable)
	void Launch();
};
