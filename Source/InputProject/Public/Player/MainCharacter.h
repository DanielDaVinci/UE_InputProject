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

	bool IsFinished() const { return Finished; }

	FDateTime GetCharacterSpawnTime() const { return CharacterSpawnTime; }
	
	void EnableMeshPhysics();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	UHealthComponent* HealthComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Camera")
	bool bCameraMovement = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera")
	float CameraSpeedPitchRotation = 1.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera")
	float CameraSpeedYawRotation = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement")
	float LandingDelay = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement")
	bool bCanMove = true;

	virtual void BeginPlay() override;

	virtual void Landed(const FHitResult& Hit) override;

	void OnDeath();

	virtual void Destroyed() override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	void ShowCursor();

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	bool Finished;

	FDateTime CharacterSpawnTime;

	void MoveForward(float Amount);
	void MoveRight(float Amount);

	void SetCharacterDirToVelocityDir();

	void PitchInput(float Amount);
	void YawInput(float Amount);

	UFUNCTION()
	void OnLandingEnd();
};
