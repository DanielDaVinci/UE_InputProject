// Input game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Traps/BaseTrap.h"
#include "MaterialShared.h"
#include "BombTrap.generated.h"

UCLASS()
class INPUTPROJECT_API ABombTrap : public ABaseTrap
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation")
	float AnimationTime = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation")
	float ReloadTime = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation")
	FVector EndScale = {1.2f, 1.2f, 1.2f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation")
	FLinearColor WarningColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation")
	FLinearColor ExplosionColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Damage")
	float Damage = 50.0f;

	UFUNCTION(BlueprintCallable)
	void SetScaleByPercent(float PercentProgress);

	UFUNCTION(BlueprintCallable)
	void SetWarningColorByPercent(float PercentProgress);

	UFUNCTION(BlueprintCallable)
	void Explode();

	UFUNCTION(BlueprintCallable)
	void Reload();

	void OnEndReload();

	UFUNCTION(BlueprintImplementableEvent)
	void StartReload();

	UFUNCTION(BlueprintImplementableEvent)
	void EndReload();

	virtual void BeginPlay() override;

private:
	UPROPERTY()
	UMaterialInstanceDynamic* DynamicMaterial;
	void SetDynamicMaterial();

	void SetSecondaryColor(FLinearColor Color);
	void SetColorBlend(float Value);
};
