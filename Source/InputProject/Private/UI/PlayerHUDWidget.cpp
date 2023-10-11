// Input game. All Rights Reserved.


#include "UI/PlayerHUDWidget.h"

#include "MainCharacter.h"
#include "Components/HealthComponent.h"

float UPlayerHUDWidget::GetHealthPercent() const
{
	UHealthComponent* HealthComponent = GetHealthComponent();
	if (!HealthComponent)
		return 0.0f;

	return HealthComponent->GetHealthPercent();
}

bool UPlayerHUDWidget::IsDeadOrDestroyed() const
{
	UHealthComponent* HealthComponent = GetHealthComponent();
	if (!HealthComponent)
		return true;

	return HealthComponent->IsDead();
}

bool UPlayerHUDWidget::IsFinished() const
{
	AMainCharacter* MainCharacter = Cast<AMainCharacter>(GetOwningPlayerPawn());
	if (!MainCharacter)
		return false;

	return MainCharacter->IsFinished();
}

UHealthComponent* UPlayerHUDWidget::GetHealthComponent() const
{
	APawn* Player = GetOwningPlayerPawn();
	if (!Player)
		return nullptr;

	return Cast<UHealthComponent>(Player->GetComponentByClass(UHealthComponent::StaticClass()));
}
