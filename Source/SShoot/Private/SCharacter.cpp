// Fill out your copyright notice in the Description page of Project Settings.


#include "SShoot/Public/SCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ASCharacter::ASCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent=CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(RootComponent);

	CameraComponent=CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);
	//Rotation
	CameraComponent->bUsePawnControlRotation=true;

	//开启蹲伏
    ACharacter::GetMovementComponent()->GetNavAgentPropertiesRef().bCanCrouch=true;
}

// Called when the game starts or when spawned
void ASCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (APlayerController* PlayerController=Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem *Subsystem=ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(IMC_Move,0);
		}
	}
}

void ASCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector=Value.Get<FVector2D>();

	if (Controller!=nullptr)
	{
		AddMovementInput(GetActorForwardVector(),MovementVector.Y);
		AddMovementInput(GetActorRightVector(),MovementVector.X);
	}
}

void ASCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(-LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ASCharacter::BeginCrouch()
{
	Crouch(true);
}

void ASCharacter::EndCrouch()
{
	UnCrouch();
}

// Called every frame
void ASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if(UEnhancedInputComponent* EnhancedInputComponent=CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (IA_Move)
		{
			EnhancedInputComponent->BindAction(IA_Move,ETriggerEvent::Triggered,this,&ASCharacter::Move);
		}

		if (IA_Look)
		{
			EnhancedInputComponent->BindAction(IA_Look,ETriggerEvent::Triggered,this,&ASCharacter::Look);
		}
		
		if (IA_Crouch)
		{
			EnhancedInputComponent->BindAction(IA_Crouch,ETriggerEvent::Triggered,this,&ASCharacter::BeginCrouch);
			EnhancedInputComponent->BindAction(IA_Crouch,ETriggerEvent::Completed,this,&ASCharacter::EndCrouch);
		}
	}

}

