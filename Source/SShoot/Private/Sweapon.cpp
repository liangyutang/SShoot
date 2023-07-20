// Fill out your copyright notice in the Description page of Project Settings.


#include "Sweapon.h"

// Sets default values
ASweapon::ASweapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent=CreateDefaultSubobject<USkeletalMeshComponent>("MeshComponent");
	RootComponent=MeshComponent;

	Range=10000.f;
}

void ASweapon::OnFire()
{
	AActor* MyOwner=GetOwner();
	if (MyOwner)
	{
		//准备参数
		FVector EyeLocation;
		FRotator EyeRotation;
		MyOwner->GetActorEyesViewPoint(EyeLocation,EyeRotation);
		FVector TraceEnd=EyeLocation+EyeRotation.Vector()*Range;
		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(MyOwner);
		QueryParams.AddIgnoredActor(this);
		QueryParams.bTraceComplex=true;
		
		FHitResult Hit;
		if (GetWorld()->LineTraceSingleByChannel(Hit,EyeLocation,TraceEnd,ECC_Visibility,QueryParams))
		{
			//设置受阻，照成伤害效果
		}
		DrawDebugLine(GetWorld(),EyeLocation,TraceEnd,FColor::White,false,1.f,0,1.f);
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

