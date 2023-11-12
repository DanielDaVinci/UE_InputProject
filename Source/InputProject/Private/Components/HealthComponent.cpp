// Input game. All Rights Reserved.


#include "Components/HealthComponent.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	SetHealth(m_maxHealth);

	AActor* Owner = GetOwner();
	if (Owner)
	{
		Owner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::OnTakeAnyDamage);
	}
}

void UHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
                                       AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage <= 0.0f || IsDead())
		return;

	SetHealth(m_health - Damage);

	if (IsDead())
	{
		OnDeath.Broadcast();
	}
}

void UHealthComponent::SetHealth(float NewHealth)
{
	m_health = FMath::Clamp(NewHealth, 0.0f, m_maxHealth);

	OnHealthChanged.Broadcast(m_health);
}
