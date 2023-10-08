// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "Components/HealthComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"

UCLASS()
class INPUTPROJECT_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMainCharacter();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	UHealthComponent* HealthComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera")
	float CameraSpeedYawRotation = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement")
	float LandingDelay = 0.5f;

	virtual void BeginPlay() override;

	virtual void Landed(const FHitResult& Hit) override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	bool CanMove = true;

	void MoveForward(float Amount);
	void MoveRight(float Amount);

	void SetCharacterDirToVelocityDir();

	void TurnAround(float Amount);

	UFUNCTION()
	void OnLandingEnd();
};
