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
	UParticleSystem* TraceEffect;

	FName TraceTargetName;

	UPROPERTY(EditDefaultsOnly,Category="Weapon")
	TSubclassOf<UCameraShakeBase> FireCamShake;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Weapon")
	UParticleSystem* DefaultImpactEffect;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Weapon")
	UParticleSystem* FleshImpactEffect;
protected:
	//播放开火相关特效
	void PlayFireEffects(const FVector& EndPoint) const;
	
public:	
	UFUNCTION(BlueprintCallable,Category="Weapon",meta=(AllowPrivateAccess="true"))
	virtual void OnFire();

};
