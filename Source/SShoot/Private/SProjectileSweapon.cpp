// Fill out your copyright notice in the Description page of Project Settings.


#include "SProjectileSweapon.h"

#include "Kismet/GameplayStatics.h"

ASProjectileSweapon::ASProjectileSweapon()
{
}

void ASProjectileSweapon::OnFire()
{
	const AActor* MyOwner=GetOwner();
	if (MyOwner&&ProjectileClass)
	{
		//准备参数
		//起始与终点位置
		FVector EyeLocation;
		FRotator EyeRotation;
		MyOwner->GetActorEyesViewPoint(EyeLocation,EyeRotation);

		//准备参数
		const FVector MuzzleLocation=MeshComponent->GetSocketLocation(MuzzleSocketName);
		/*const FRotator MuzzleRotation=MeshComponent->GetSocketRotation(MuzzleSocketName);*/
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride=ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		GetWorld()->SpawnActor<AActor>(ProjectileClass,MuzzleLocation,EyeRotation,SpawnParameters);
	}
}
