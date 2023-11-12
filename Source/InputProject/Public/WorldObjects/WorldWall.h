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
	USceneComponent* m_pSceneComponent;

	UPROPERTY(VisibleAnywhere, Category="Components")
	UBoxComponent* m_pCollisionComponent;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
};
