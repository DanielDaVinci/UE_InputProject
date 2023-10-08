// Input game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "BaseTrap.generated.h"

UCLASS()
class INPUTPROJECT_API ABaseTrap : public AActor
{
	GENERATED_BODY()

public:
	ABaseTrap();

protected:
	UPROPERTY(VisibleAnywhere, Category="Components")
	USceneComponent* SceneComponent;
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UBoxComponent* CollisionComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* StaticMeshComponent;

	virtual void BeginPlay() override;
};
