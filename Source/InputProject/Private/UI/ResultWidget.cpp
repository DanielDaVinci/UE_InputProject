// Input game. All Rights Reserved.


#include "UI/ResultWidget.h"

#include "MainCharacter.h"
#include "Blueprint/WidgetTree.h"
#include "Components/TextBlock.h"

bool UResultWidget::IsFinished() const
{
	AMainCharacter* MainCharacter = Cast<AMainCharacter>(GetOwningPlayerPawn());
	if (!MainCharacter)
		return false;

	return MainCharacter->IsFinished();
}

FTimespan UResultWidget::GetLifeTime() const
{
	static FDateTime GameStartTime = FDateTime::Now();
	static FDateTime GameEndTime = FDateTime::Now();

	AMainCharacter* MainCharacter = Cast<AMainCharacter>(GetOwningPlayerPawn());
	if (!MainCharacter || MainCharacter->IsFinished())
		return GameEndTime - GameStartTime;

	UHealthComponent* HealthComponent = Cast<UHealthComponent>(MainCharacter->GetComponentByClass(UHealthComponent::StaticClass()));
	if (HealthComponent->IsDead())
		return GameEndTime - GameStartTime;

	GameStartTime = MainCharacter->GetCharacterSpawnTime();
	GameEndTime = FDateTime::Now();

	return GameEndTime - GameStartTime;
}

void UResultWidget::ResetLevel()
{
}

UHealthComponent* UResultWidget::GetHealthComponent() const
{
	APawn* Player = GetOwningPlayerPawn();
	if (!Player)
		return nullptr;

	return Cast<UHealthComponent>(Player->GetComponentByClass(UHealthComponent::StaticClass()));
}
