// Input game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/HealthComponent.h"
#include "ResultWidget.generated.h"

UCLASS()
class INPUTPROJECT_API UResultWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintCallable, Category="UI")
	bool IsFinished() const;

	UFUNCTION(BlueprintCallable, Category="UI")
	FTimespan GetLifeTime() const;

	UFUNCTION(BlueprintCallable, Category="UI")
	void RestartLevel();

private:
	UHealthComponent* GetHealthComponent() const;
};
