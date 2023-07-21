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

	FTimerHandle TimerHandle_TimeBetweenShots;

	//开火速率，每分钟射出子弹的个数
	UPROPERTY(EditDefaultsOnly,Category="Weapon")
	float RateFire;

	float LastTimeFired;

	//开火间隔
	float TimeBetweenShots;

protected:
	//播放开火相关特效
	void PlayFireEffects(const FVector& EndPoint) const;

	UFUNCTION(BlueprintCallable,Category="Weapon",meta=(AllowPrivateAccess="true"))
	virtual void OnFire();

	virtual void BeginPlay() override;
	
public:	
	//设置自动开火(开火间隔)
	void StartFire();

	//停止自动开火
	void StopFire();

};
