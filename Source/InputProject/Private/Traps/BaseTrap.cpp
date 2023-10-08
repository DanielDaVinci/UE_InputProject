// Input game. All Rights Reserved.


#include "Traps/BaseTrap.h"

ABaseTrap::ABaseTrap()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);
	
	CollisionComponent = CreateDefaultSubobject<UBoxComponent>("CollisionComponent");
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	CollisionComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	CollisionComponent->SetupAttachment(GetRootComponent());

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	StaticMeshComponent->SetCollisionResponseToAllChannels(ECR_Block);
	StaticMeshComponent->SetupAttachment(GetRootComponent());
}

void ABaseTrap::BeginPlay()
{
	Super::BeginPlay();
	
}

