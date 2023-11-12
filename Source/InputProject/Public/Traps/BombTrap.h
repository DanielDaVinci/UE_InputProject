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
	float m_animationTime = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation")
	float m_reloadTime = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation")
	FVector m_endScale = {1.2f, 1.2f, 1.2f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation")
	FLinearColor m_warningColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation")
	FLinearColor m_explosionColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Damage")
	float m_damage = 50.0f;

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
	UMaterialInstanceDynamic* m_dynamicMaterial;
	void SetDynamicMaterial();

	void SetSecondaryColor(FLinearColor Color);
	void SetColorBlend(float Value);
};
