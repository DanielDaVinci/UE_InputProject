// Input game. All Rights Reserved.


#include "Traps/BombTrap.h"

#include "MainCharacter.h"
#include "Kismet/GameplayStatics.h"

void ABombTrap::SetScaleByPercent(float PercentProgress)
{
	const FVector NewScale = (EndScale - FVector::OneVector) * PercentProgress + FVector::OneVector;
	SetActorScale3D(NewScale);
}

void ABombTrap::SetWarningColorByPercent(float PercentProgress)
{
	if (!DynamicMaterial)
		return;

	SetColorBlend(PercentProgress);
}

void ABombTrap::Explode()
{
	TArray<AActor*> OverlapActors;
	GetOverlappingActors(OverlapActors, AMainCharacter::StaticClass());
	
	for (AActor* Actor : OverlapActors)
	{
		UGameplayStatics::ApplyDamage(Actor, Damage, nullptr, this, nullptr);
	}
}

void ABombTrap::Reload()
{
	StartReload();
	
	SetSecondaryColor(ExplosionColor);
    CollisionComponent->SetGenerateOverlapEvents(false);
    
    auto fun = [this]()
    {
    	SetSecondaryColor(WarningColor);
    	CollisionComponent->SetGenerateOverlapEvents(true);
    	CollisionComponent->UpdateOverlaps();

    	EndReload();
    };

    FTimerHandle ReloadTimer;
    GetWorldTimerManager().SetTimer(ReloadTimer, fun, ReloadTime, false);
}

void ABombTrap::BeginPlay()
{
	Super::BeginPlay();

	SetDynamicMaterial();
	SetSecondaryColor(WarningColor);
}

void ABombTrap::SetDynamicMaterial()
{
	if (!StaticMeshComponent)
		return;

	UMaterialInterface* Material = StaticMeshComponent->GetMaterial(0);
	if (!Material)
		return;

	DynamicMaterial = UMaterialInstanceDynamic::Create(Material, nullptr);
	StaticMeshComponent->SetMaterial(0, DynamicMaterial);
}

void ABombTrap::SetSecondaryColor(FLinearColor Color)
{
	if (!DynamicMaterial)
		return;

	DynamicMaterial->SetVectorParameterValue(TEXT("Secondary Color"), Color);
}

void ABombTrap::SetColorBlend(float Value)
{
	if (!DynamicMaterial)
		return;

	DynamicMaterial->SetScalarParameterValue(TEXT("Blend"), Value);
}
