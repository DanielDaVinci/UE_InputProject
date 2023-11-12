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
	USceneComponent* m_pSceneComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UBoxComponent* m_pCollisionComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* m_pStaticMeshComponent;
};
