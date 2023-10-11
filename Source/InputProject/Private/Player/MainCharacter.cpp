// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/MainCharacter.h"

#include "Components/ArrowComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "WorldObjects/FinishSpace.h"


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

	Finished = false;
	CharacterSpawnTime = FDateTime::Now();

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

	PlayerInputComponent->BindAxis("LookUp", this, &AMainCharacter::PitchInput);
	PlayerInputComponent->BindAxis("TurnAround", this, &AMainCharacter::YawInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMainCharacter::Jump);
}

void AMainCharacter::MoveForward(float Amount)
{
	if (!bCanMove || !CameraComponent)
		return;
	
	AddMovementInput(CameraComponent->GetForwardVector().GetSafeNormal2D(), Amount);

	SetCharacterDirToVelocityDir();
}

void AMainCharacter::MoveRight(float Amount)
{
	if (!bCanMove || !CameraComponent)
		return;
	
	AddMovementInput(CameraComponent->GetRightVector().GetSafeNormal2D(), Amount);

	SetCharacterDirToVelocityDir();
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

void AMainCharacter::PitchInput(float Amount)
{
	if (!bCameraMovement)
		return;
	
	AddControllerPitchInput(Amount * CameraSpeedPitchRotation);
}

void AMainCharacter::YawInput(float Amount)
{
	if (!bCameraMovement)
		return;
	
	FRotator Rotation = SpringArmComponent->GetRelativeRotation();
	Rotation.Yaw += Amount * CameraSpeedYawRotation;

	SpringArmComponent->SetRelativeRotation(Rotation);
}

void AMainCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);

	bCanMove = false;
	FTimerHandle LandingTimerHandle;
	GetWorldTimerManager().SetTimer(LandingTimerHandle, this, &AMainCharacter::OnLandingEnd, LandingDelay, false);
}

void AMainCharacter::OnDeath()
{
	ShowCursor();
	this->bCameraMovement = false;
	GetCharacterMovement()->DisableMovement();
	
	EnableMeshPhysics();
}

void AMainCharacter::Destroyed()
{
	HealthComponent->OnDeath.Broadcast();
	
	Super::Destroyed();
}

void AMainCharacter::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	
	if (OtherActor->IsA<AFinishSpace>())
	{
		Finished = true;

		ShowCursor();
		this->bCameraMovement = false;
		GetCharacterMovement()->DisableMovement();
	}
}

void AMainCharacter::ShowCursor()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (!PlayerController)
		return;
	
	PlayerController->bShowMouseCursor = true;
}

void AMainCharacter::EnableMeshPhysics()
{
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Ignore);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetMesh()->SetSimulatePhysics(true);
}

void AMainCharacter::OnLandingEnd()
{
	bCanMove = true;
}
