// Input game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ResultWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/HealthComponent.h"
#include "PlayerHUDWidget.generated.h"


UCLASS()
class INPUTPROJECT_API UPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	UFUNCTION(BlueprintCallable, Category="UI")
	float GetHealthPercent() const;

	UFUNCTION(BlueprintCallable, Category="UI")
	bool IsDeadOrDestroyed() const;

	UFUNCTION(BlueprintCallable, Category="UI")
	bool IsFinished() const;
	
private:
	
	UHealthComponent* GetHealthComponent() const;
};
