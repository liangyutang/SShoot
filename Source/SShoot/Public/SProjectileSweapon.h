// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Sweapon.h"
#include "SProjectileSweapon.generated.h"

/**
 * 
 */
UCLASS()
class SSHOOT_API ASProjectileSweapon : public ASweapon
{
	GENERATED_BODY()

protected:
	ASProjectileSweapon();

	UPROPERTY(EditDefaultsOnly,Category="Weapon")
	TSubclassOf<AActor> ProjectileClass;
	
protected:
	virtual void OnFire() override;
};
