// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/MainCharacter.h"

#include "Components/ArrowComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PawnMovementComponent.h"


AMainCharacter::AMainCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->bInheritYaw = false;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>("HealthComponent");
}


void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();

	check(GetCharacterMovement());
	check(GetMesh());

	HealthComponent->OnDeath.AddUObject(this, &AMainCharacter::OnDeath);

	SpringArmComponent->SetRelativeRotation(GetActorRotation());
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

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMainCharacter::Jump);
}

void AMainCharacter::SetCharacterDirToVelocityDir()
{
	if (!GetMesh() || GetVelocity().Size() == 0.0f)
		return;

	float VelocityYawRotation = GetVelocity().ToOrientationRotator().Yaw;

	FRotator Rotation = GetMesh()->GetComponentRotation();
	Rotation.Yaw = VelocityYawRotation - 90.0f;

	GetMesh()->SetWorldRotation(Rotation);
}

void AMainCharacter::MoveForward(float Amount)
{
	if (!CameraComponent || !CanMove)
		return;

	AddMovementInput(CameraComponent->GetForwardVector(), Amount);

	SetCharacterDirToVelocityDir();
}

void AMainCharacter::MoveRight(float Amount)
{
	if (!CameraComponent || !CanMove)
		return;

	AddMovementInput(CameraComponent->GetRightVector(), Amount);

	SetCharacterDirToVelocityDir();
}

void AMainCharacter::TurnAround(float Amount)
{
	FRotator Rotation = SpringArmComponent->GetRelativeRotation();
	Rotation.Yaw += Amount * CameraSpeedYawRotation;

	SpringArmComponent->SetRelativeRotation(Rotation);
}

void AMainCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);

	CanMove = false;
	FTimerHandle LandingTimerHandle;
	GetWorldTimerManager().SetTimer(LandingTimerHandle, this, &AMainCharacter::OnLandingEnd, LandingDelay, false);
}

void AMainCharacter::OnDeath()
{
	GetCharacterMovement()->DisableMovement();
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Ignore);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetMesh()->SetSimulatePhysics(true);
}

void AMainCharacter::OnLandingEnd()
{
	CanMove = true;
}
