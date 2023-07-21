// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SHealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_SixParams(FOnHealthChangedSignature, USHealthComponent*, HealthComp, float, Health,
                                          float, HealthDelta, const class UDamageType*, DamageType, class AController*, InstigatedBy,
                                          AActor*, DamageCauser);

UCLASS( ClassGroup=(COOP), meta=(BlueprintSpawnableComponent) )
class SSHOOT_API USHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USHealthComponent();

protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="HealthComponent")
	float Health;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="HealthComponent")
	float DefaultHealth;

	USHealthComponent* HealthComponent;
protected:
	UFUNCTION()
	void HandleTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	UPROPERTY(BlueprintAssignable,Category="Event")
	FOnHealthChangedSignature OnHealthChanged;
};
