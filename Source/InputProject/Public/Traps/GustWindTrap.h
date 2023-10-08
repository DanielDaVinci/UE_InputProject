// Input game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Traps/BaseTrap.h"
#include "GustWindTrap.generated.h"

UCLASS()
class INPUTPROJECT_API AGustWindTrap : public ABaseTrap
{
	GENERATED_BODY()

public:
	AGustWindTrap();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement")
	float WindForce = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement")
	float WindChangeFrequency = 2.0f;

	UFUNCTION()
	void ChangeRandomWindDirection();

	virtual void BeginPlay() override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

	void MoveTrappedActors(float DeltaTime);
	
public:
	virtual void Tick(float DeltaTime) override;

private:
	FVector2D CurrentWindDirection;

	FTimerHandle DirectionChangeTimer;

	UPROPERTY()
	TArray<AActor*> TrappedActors;
};
