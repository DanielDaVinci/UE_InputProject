// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/MainCharacter.h"

#include "Components/ArrowComponent.h"


AMainCharacter::AMainCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->bInheritYaw = false;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);
}


void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();

	check(GetMesh());
}


void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMainCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMainCharacter::MoveRight);

	PlayerInputComponent->BindAxis("LookUp", this, &AMainCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnAround", this, &AMainCharacter::TurnAround);
}

void AMainCharacter::SetCharacterDirToVelocityDir()
{
	if (!GetMesh() || GetVelocity().Size() == 0.0f)
		return;
	
	FRotator Rotation = GetVelocity().ToOrientationRotator();
	Rotation.Yaw -= 90.0f;
	
	GetMesh()->SetWorldRotation(Rotation);
}

void AMainCharacter::MoveForward(float Amount)
{
	AddMovementInput(CameraComponent->GetForwardVector(), Amount);

	SetCharacterDirToVelocityDir();
}

void AMainCharacter::MoveRight(float Amount)
{
	AddMovementInput(CameraComponent->GetRightVector(), Amount);

	SetCharacterDirToVelocityDir();
}

void AMainCharacter::TurnAround(float Amount)
{
	FRotator Rotation = SpringArmComponent->GetRelativeRotation();
	Rotation.Yaw += Amount * CameraSpeedYawRotation;
	
	SpringArmComponent->SetRelativeRotation(Rotation);
}

