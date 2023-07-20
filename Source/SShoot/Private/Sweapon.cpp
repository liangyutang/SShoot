// Fill out your copyright notice in the Description page of Project Settings.


#include "Sweapon.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
ASweapon::ASweapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent=CreateDefaultSubobject<USkeletalMeshComponent>("MeshComponent");
	RootComponent=MeshComponent;

	Range=10000.f;
	Damage=20.f;
	MuzzleSocketName="MuzzleSocket";
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
		
		if (GetWorld()->LineTraceSingleByChannel(Hit,EyeLocation,TraceEnd,ECC_Visibility,QueryParams))
		{
			//设置受阻，照成伤害效果
			//打中的物体
			AActor* HitActor=Hit.GetActor();
			//射击方位
			FVector ShotDirection=EyeRotation.Vector();
			
			UGameplayStatics::ApplyPointDamage(HitActor,Damage,ShotDirection,Hit,MyOwner->GetInstigatorController(),this,DamageType);

			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),ImpactEffect,Hit.ImpactPoint,Hit.ImpactNormal.Rotation());
		}
		DrawDebugLine(GetWorld(),EyeLocation,TraceEnd,FColor::White,false,1.f,0,1.f);
		//播放特效
		if (MuzzleEffect)
		{
			UGameplayStatics::SpawnEmitterAttached(MuzzleEffect,MeshComponent,MuzzleSocketName);
		}
	}
	
}

// Called when the game starts or when spawned
void ASweapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASweapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

