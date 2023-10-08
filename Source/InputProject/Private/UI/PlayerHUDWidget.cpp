// Input game. All Rights Reserved.


#include "UI/PlayerHUDWidget.h"

#include "Components/HealthComponent.h"

bool UPlayerHUDWidget::Initialize()
{
	return Super::Initialize();
}

float UPlayerHUDWidget::GetHealthPercent() const
{
	UHealthComponent* HealthComponent = GetHealthComponent();
	if (!HealthComponent)
		return 0.0f;

	return HealthComponent->GetHealthPercent();
}

bool UPlayerHUDWidget::IsDead() const
{
	UHealthComponent* HealthComponent = GetHealthComponent();
	if (!HealthComponent)
		return true;

	return HealthComponent->IsDead();
}

UHealthComponent* UPlayerHUDWidget::GetHealthComponent() const
{
	APawn* Player = GetOwningPlayerPawn();
	if (!Player)
		return nullptr;

	return Cast<UHealthComponent>(Player->GetComponentByClass(UHealthComponent::StaticClass()));
}
