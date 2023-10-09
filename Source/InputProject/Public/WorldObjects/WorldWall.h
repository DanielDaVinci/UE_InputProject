// Input game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "WorldWall.generated.h"

UCLASS()
class INPUTPROJECT_API AWorldWall : public AActor
{
	GENERATED_BODY()

public:
	AWorldWall();

protected:
	UPROPERTY(VisibleAnywhere, Category="Components")
	USceneComponent* SceneComponent;

	UPROPERTY(VisibleAnywhere, Category="Components")
	UBoxComponent* CollisionComponent;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
};
