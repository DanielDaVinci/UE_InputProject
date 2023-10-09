// Input game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "FinishSpace.generated.h"

UCLASS()
class INPUTPROJECT_API AFinishSpace : public AActor
{
	GENERATED_BODY()

public:
	AFinishSpace();

protected:
	UPROPERTY(VisibleAnywhere, Category="Components")
	USceneComponent* SceneComponent;

	UPROPERTY(VisibleAnywhere, Category="Components")
	UBoxComponent* CollisionComponent;
};
