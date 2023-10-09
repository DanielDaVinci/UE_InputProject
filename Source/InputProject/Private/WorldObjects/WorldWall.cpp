// Input game. All Rights Reserved.


#include "WorldObjects/WorldWall.h"

#include "MainCharacter.h"
#include "Components/HealthComponent.h"
#include "Kismet/GameplayStatics.h"

AWorldWall::AWorldWall()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);

	CollisionComponent = CreateDefaultSubobject<UBoxComponent>("CollisionComponent");
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	CollisionComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	CollisionComponent->SetupAttachment(GetRootComponent());
	CollisionComponent->SetupAttachment(SceneComponent);
}

void AWorldWall::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	OtherActor->Destroy();
}

