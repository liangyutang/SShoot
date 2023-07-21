// Fill out your copyright notice in the Description page of Project Settings.


#include "Sweapon.h"

#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "SShoot/SShoot.h"

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
		QueryParams.bReturnPhysicalMaterial=true;
		
		FHitResult Hit;

		FVector TraceEndPoint=TraceEnd;
		
		if (GetWorld()->LineTraceSingleByChannel(Hit,EyeLocation,TraceEnd,ECC_Visibility,QueryParams))
		{
			//设置受阻，照成伤害效果
			//打中的物体
			AActor* HitActor=Hit.GetActor();
			//获取击中的表面
			EPhysicalSurface SurfaceType= UPhysicalMaterial::DetermineSurfaceType(Hit.PhysMaterial.Get());
			//射击方位
			FVector ShotDirection=EyeRotation.Vector();
			UGameplayStatics::ApplyPointDamage(HitActor,Damage,ShotDirection,Hit,MyOwner->GetInstigatorController(),this,DamageType);

			
			UParticleSystem* SelectEffect=nullptr;
			
			switch (SurfaceType)
			{
			case SURFACE_FLESHDEFAULT :
			case SURFACE_FLESHVULUERABLE :
				SelectEffect=FleshImpactEffect;
				break;
			default:
				SelectEffect=DefaultImpactEffect;
			}

			//击中特效
			if (SelectEffect)
			{
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),SelectEffect,Hit.ImpactPoint,Hit.ImpactNormal.Rotation());
			}
			
			TraceEndPoint=Hit.ImpactPoint;
		}
		if (DebugWeaponDrawing>0)
		{
			DrawDebugLine(GetWorld(),EyeLocation,TraceEnd,FColor::White,false,1.f,0,1.f);
		}

		//特效
		PlayFireEffects(TraceEndPoint);
	}
	
}

void ASweapon::PlayFireEffects(const FVector& EndPoint) const
{
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
			TraceComponent->SetVectorParameter(TraceTargetName,EndPoint);
		}
	}
	//抖动效果
	if (const APawn* MyOwner=Cast<APawn>(GetOwner()))
	{
		if (APlayerController *PC=Cast<APlayerController>(MyOwner->GetInstigatorController()))
		{
			PC->ClientStartCameraShake(FireCamShake);
		}
	}
}

