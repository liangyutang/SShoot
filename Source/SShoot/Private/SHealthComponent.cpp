// Fill out your copyright notice in the Description page of Project Settings.


#include "SHealthComponent.h"

// Sets default values for this component's properties
USHealthComponent::USHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.

	DefaultHealth=100.f;
	Health=DefaultHealth;
	// ...
}


void USHealthComponent::HandleTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
	AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage<=0.f)
	{
		return;
	}
	Health=FMath::Clamp(Health-Damage,0.0f,DefaultHealth);
	UE_LOG(LogTemp,Log,TEXT("%f"),Health);
}

// Called when the game starts
void USHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	if (AActor* MyOwner=GetOwner())
	{
		MyOwner->OnTakeAnyDamage.AddDynamic(this,&USHealthComponent::HandleTakeAnyDamage);
	}
	
}

