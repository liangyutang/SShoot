// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SCharacter.generated.h"

UCLASS()
class SSHOOT_API ASCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Move(const struct FInputActionValue &Value);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Input|Context",meta=(AllowPrivateAccess="true"))
	class UInputMappingContext* IMC_Move;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Input|Context",meta=(AllowPrivateAccess="true"))
	class UInputAction* IA_Move;
};
