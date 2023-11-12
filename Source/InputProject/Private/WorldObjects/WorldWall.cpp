// Input game. All Rights Reserved.


#include "WorldObjects/WorldWall.h"

#include "MainCharacter.h"
#include "Components/HealthComponent.h"
#include "Kismet/GameplayStatics.h"

AWorldWall::AWorldWall()
{
	PrimaryActorTick.bCanEverTick = false;

	m_pSceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(m_pSceneComponent);

	m_pCollisionComponent = CreateDefaultSubobject<UBoxComponent>("CollisionComponent");
	m_pCollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	m_pCollisionComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	m_pCollisionComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	m_pCollisionComponent->SetupAttachment(GetRootComponent());
	m_pCollisionComponent->SetupAttachment(m_pSceneComponent);
}

void AWorldWall::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	OtherActor->Destroy();
}

