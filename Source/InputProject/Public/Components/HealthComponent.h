// Input game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDeath);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class INPUTPROJECT_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UHealthComponent();

	FOnDeath OnDeath;
	FOnHealthChanged OnHealthChanged;

	UFUNCTION(BlueprintCallable, Category = "Health")
	bool IsDead() const { return FMath::IsNearlyZero(m_health); }

	UFUNCTION(BlueprintCallable, Category = "Health")
	float GetHealthPercent() const { return m_health / m_maxHealth; }

	float GetMaxHealth() const { return m_maxHealth; }

	float GetHealth() const { return m_health; }

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Health", meta = (ClampMin="0.0"))
	float m_maxHealth = 100.0f;

	virtual void BeginPlay() override;

private:
	float m_health = 0.0f;

	UFUNCTION()
	void OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType,
	                     class AController* InstigatedBy, AActor* DamageCauser);

	void SetHealth(float NewHealth);
};
