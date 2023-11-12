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

	bool IsFinished() const { return m_bFinished; }

	FDateTime GetCharacterSpawnTime() const { return m_characterSpawnTime; }

	void EnableMeshPhysics();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	USpringArmComponent* m_pSpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	UCameraComponent* m_pCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	UHealthComponent* m_pHealthComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Camera")
	bool m_bCameraMovement = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera")
	float m_cameraSpeedPitchRotation = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera")
	float m_cameraSpeedYawRotation = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement")
	float m_landingDelay = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement")
	bool m_bCanMove = true;

	virtual void BeginPlay() override;

	virtual void Landed(const FHitResult& Hit) override;

	void OnDeath();

	virtual void Destroyed() override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	void ShowCursor();

	void SetInputOnGame();

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	bool m_bFinished;

	FDateTime m_characterSpawnTime;

	void MoveForward(float Amount);
	void MoveRight(float Amount);

	void SetCharacterDirToVelocityDir();

	void PitchInput(float Amount);
	void YawInput(float Amount);

	UFUNCTION()
	void OnLandingEnd();

	void QuitGame();
};
