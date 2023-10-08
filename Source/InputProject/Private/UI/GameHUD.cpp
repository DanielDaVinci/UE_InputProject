// Input game. All Rights Reserved.


#include "UI/GameHUD.h"

#include "Blueprint/UserWidget.h"

void AGameHUD::BeginPlay()
{
	Super::BeginPlay();

	UUserWidget* PlayerHUDWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerHUDWidgetClass);
	if (PlayerHUDWidget)
	{
		PlayerHUDWidget->AddToViewport();
	}
}
