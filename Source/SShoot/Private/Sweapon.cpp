// Fill out your copyright notice in the Description page of Project Settings.


#include "Sweapon.h"

#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

//控制台debug显示控制
static int32 DebugWeaponDrawing=0;
FAutoConsoleVariableRef CVARDebugWeaponDrawing(TEXT("COOP.DebugWeapons"),DebugWeaponDrawing,TEXT("Draw Debug Lines for Weapons"),ECVF_Cheat);

// Sets default values
ASweapon::ASweapon()
{
	MeshComponent=CreateDefaultSubobject<USkeletalMeshComponent>("MeshComponent");
	RootComponent=MeshComponent;

	Range=10000.f;
	Damage=20.f;
	MuzzleSocketName="MuzzleSocket";
	TraceTargetName="Target";
}

void ASweapon::OnFire()
{
	if (AActor* MyOwner=GetOwner())
	{
		//准备参数
		//起始与终点位置
		FVector EyeLocation;
		FRotator EyeRotation;
		MyOwner->GetActorEyesViewPoint(EyeLocation,EyeRotation);
		//终点位置
		FVector TraceEnd=EyeLocation+EyeRotation.Vector()*Range;
		//查询参数
		FCollisionQueryParams QueryParams;
		//忽略的Actor
		QueryParams.AddIgnoredActor(MyOwner);
		QueryParams.AddIgnoredActor(this);
		//复杂追踪
		QueryParams.bTraceComplex=true;
		
		FHitResult Hit;

		TraceEndPoint=TraceEnd;
		
		if (GetWorld()->LineTraceSingleByChannel(Hit,EyeLocation,TraceEnd,ECC_Visibility,QueryParams))
		{
			//设置受阻，照成伤害效果
			//打中的物体
			AActor* HitActor=Hit.GetActor();
			//射击方位
			FVector ShotDirection=EyeRotation.Vector();
			
			UGameplayStatics::ApplyPointDamage(HitActor,Damage,ShotDirection,Hit,MyOwner->GetInstigatorController(),this,DamageType);
			if (ImpactEffect)
			{
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),ImpactEffect,Hit.ImpactPoint,Hit.ImpactNormal.Rotation());
			}
			TraceEndPoint=Hit.ImpactPoint;
		}
		if (DebugWeaponDrawing>0)
		{
			DrawDebugLine(GetWorld(),EyeLocation,TraceEnd,FColor::White,false,1.f,0,1.f);
		}
		//播放开火特效
		if (MuzzleEffect)
		{
			UGameplayStatics::SpawnEmitterAttached(MuzzleEffect,MeshComponent,MuzzleSocketName);
		}
		//创建发射特效
		if (TraceEffect)
		{
			FVector MuzzleLocation=MeshComponent->GetSocketLocation(MuzzleSocketName);
			if (UParticleSystemComponent* TraceComponent= UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),TraceEffect,MuzzleLocation))
			{
				TraceComponent->SetVectorParameter(TraceTargetName,TraceEndPoint);
			}
		}
	}
	
}

void ASweapon::PlayFireEffects()
{
	
}

