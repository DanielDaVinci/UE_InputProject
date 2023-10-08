// Input game. All Rights Reserved.


#include "UI/PlayerHUDWidget.h"

#include "Components/HealthComponent.h"

bool UPlayerHUDWidget::Initialize()
{
	APawn* Player = GetOwningPlayerPawn();
	if (!Player)
		return 0.0f;
	
	UHealthComponent* HealthComponent = Cast<UHealthComponent>(Player->GetComponentByClass(UHealthComponent::StaticClass()));
	if (!HealthComponent)
		return 0.0f;
	
	return Super::Initialize();
}

float UPlayerHUDWidget::GetHealthPercent() const
{
	APawn* Player = GetOwningPlayerPawn();
	if (!Player)
		return 0.0f;
	
	UHealthComponent* HealthComponent = Cast<UHealthComponent>(Player->GetComponentByClass(UHealthComponent::StaticClass()));
	if (!HealthComponent)
		return 0.0f;

	return HealthComponent->GetHealthPercent();
}

bool UPlayerHUDWidget::IsDead() const
{
	APawn* Player = GetOwningPlayerPawn();
	if (!Player)
		return false;
	
	UHealthComponent* HealthComponent = Cast<UHealthComponent>(Player->GetComponentByClass(UHealthComponent::StaticClass()));
	if (!HealthComponent)
		return false;

	return HealthComponent->IsDead();
}
