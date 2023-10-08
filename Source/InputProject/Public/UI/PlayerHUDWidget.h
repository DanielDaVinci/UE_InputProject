// Input game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHUDWidget.generated.h"


UCLASS()
class INPUTPROJECT_API UPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual bool Initialize() override;

	UFUNCTION(BlueprintCallable, Category="UI")
	float GetHealthPercent() const;

	UFUNCTION(BlueprintCallable, Category="UI")
	bool IsDead() const;
};
