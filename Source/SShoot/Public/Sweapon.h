// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sweapon.generated.h"

UCLASS()
class SSHOOT_API ASweapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASweapon();

protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Components")
	USkeletalMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Weapon")
	float Range;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Weapon")
	float Damage;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Weapon")
	TSubclassOf<UDamageType> DamageType;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Weapon")
	UParticleSystem* MuzzleEffect;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Weapon")
	FName MuzzleSocketName;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Weapon")
	UParticleSystem* ImpactEffect;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Weapon")
	UParticleSystem* TraceEffect;
	
	FVector TraceEndPoint;

	FName TraceTargetName;

protected:
	UFUNCTION(BlueprintCallable,Category="Weapon")
	virtual void OnFire();

	//播放开火时特效
	void PlayFireEffects();
public:	
	

};
