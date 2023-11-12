// Input game. All Rights Reserved.


#include "WorldObjects/FinishSpace.h"

AFinishSpace::AFinishSpace()
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

