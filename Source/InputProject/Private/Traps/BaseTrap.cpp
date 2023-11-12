// Input game. All Rights Reserved.


#include "Traps/BaseTrap.h"

ABaseTrap::ABaseTrap()
{
	PrimaryActorTick.bCanEverTick = false;

	m_pSceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(m_pSceneComponent);
	
	m_pCollisionComponent = CreateDefaultSubobject<UBoxComponent>("CollisionComponent");
	m_pCollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	m_pCollisionComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	m_pCollisionComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	m_pCollisionComponent->SetupAttachment(GetRootComponent());

	m_pStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	m_pStaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	m_pStaticMeshComponent->SetCollisionResponseToAllChannels(ECR_Block);
	m_pStaticMeshComponent->SetupAttachment(GetRootComponent());
}

