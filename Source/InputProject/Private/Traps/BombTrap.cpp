// Input game. All Rights Reserved.


#include "Traps/BombTrap.h"

#include "MainCharacter.h"
#include "Kismet/GameplayStatics.h"

void ABombTrap::SetScaleByPercent(float PercentProgress)
{
	const FVector NewScale = (m_endScale - FVector::OneVector) * PercentProgress + FVector::OneVector;
	SetActorScale3D(NewScale);
}

void ABombTrap::SetWarningColorByPercent(float PercentProgress)
{
	if (!m_dynamicMaterial)
		return;

	SetColorBlend(PercentProgress);
}

void ABombTrap::Explode()
{
	TArray<AActor*> OverlapActors;
	GetOverlappingActors(OverlapActors, AMainCharacter::StaticClass());
	
	for (AActor* Actor : OverlapActors)
	{
		UGameplayStatics::ApplyDamage(Actor, m_damage, nullptr, this, nullptr);
	}
}

void ABombTrap::Reload()
{
	StartReload();
	
	SetSecondaryColor(m_explosionColor);
    m_pCollisionComponent->SetGenerateOverlapEvents(false);

    FTimerHandle ReloadTimer;
    GetWorldTimerManager().SetTimer(ReloadTimer, this, &ABombTrap::OnEndReload, m_reloadTime, false);
}

void ABombTrap::OnEndReload()
{
	SetSecondaryColor(m_warningColor);
	m_pCollisionComponent->SetGenerateOverlapEvents(true);
	m_pCollisionComponent->UpdateOverlaps();

	EndReload();
}

void ABombTrap::BeginPlay()
{
	Super::BeginPlay();

	SetDynamicMaterial();
	SetSecondaryColor(m_warningColor);
}

void ABombTrap::SetDynamicMaterial()
{
	if (!m_pStaticMeshComponent)
		return;

	UMaterialInterface* Material = m_pStaticMeshComponent->GetMaterial(0);
	if (!Material)
		return;

	m_dynamicMaterial = UMaterialInstanceDynamic::Create(Material, nullptr);
	m_pStaticMeshComponent->SetMaterial(0, m_dynamicMaterial);
}

void ABombTrap::SetSecondaryColor(FLinearColor Color)
{
	if (!m_dynamicMaterial)
		return;

	m_dynamicMaterial->SetVectorParameterValue(TEXT("Secondary Color"), Color);
}

void ABombTrap::SetColorBlend(float Value)
{
	if (!m_dynamicMaterial)
		return;

	m_dynamicMaterial->SetScalarParameterValue(TEXT("Blend"), Value);
}
