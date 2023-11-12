// Input game. All Rights Reserved.


#include "UI/GameHUD.h"

#include "Blueprint/UserWidget.h"

void AGameHUD::BeginPlay()
{
	Super::BeginPlay();

	UUserWidget* PlayerHUDWidget = CreateWidget<UUserWidget>(GetWorld(), m_playerHUDWidgetClass);
	if (PlayerHUDWidget)
	{
		PlayerHUDWidget->AddToViewport();
	}
}
