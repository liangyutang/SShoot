// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SCharacter.generated.h"

class ASweapon;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class SSHOOT_API ASCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASCharacter();

protected:

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Components")
	USpringArmComponent* SpringArmComponent;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Components")
	UCameraComponent* CameraComponent;

	//是否开启变焦推进
	bool bWantsToZoom;

	//变焦的视野范围
	UPROPERTY(EditDefaultsOnly,Category="Player")
	float ZoomFOV;

	//初始视野范围
	float DefaultFOV;

	//变焦速度
	UPROPERTY(EditDefaultsOnly,Category="Player",meta=(ClampMin=0.1,ClampMax=100))
	float ZoomInterpSpeed;

	//当前携带的武器
	UPROPERTY()
	ASweapon* CurrentWeapon;

	//生成武器的类
	UPROPERTY(EditDefaultsOnly,Category="Player")
	TSubclassOf<ASweapon> StarterWeaponClass;

	UPROPERTY(VisibleDefaultsOnly,Category="Player")
	FName WeaponAttachSocketName;

	//准心
	UPROPERTY(EditDefaultsOnly,Category="Player")
	TSubclassOf<UUserWidget> WBP_Cross;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Move(const struct FInputActionValue &Value);

	void Look(const struct FInputActionValue &Value);

	void BeginCrouch();

	void EndCrouch();

	void BeginZoom(const FInputActionValue& InputActionValue);
	
	void EndZoom(const FInputActionValue& InputActionValue);

	virtual FVector GetPawnViewLocation() const override;

	void OnFire();
	

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

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Input|Context",meta=(AllowPrivateAccess="true"))
	class UInputAction* IA_Look;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Input|Context",meta=(AllowPrivateAccess="true"))
	class UInputAction* IA_Crouch;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Input|Context",meta=(AllowPrivateAccess="true"))
	class UInputAction* IA_Zoom;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Input|Context",meta=(AllowPrivateAccess="true"))
	class UInputAction* IA_Fire;
};
