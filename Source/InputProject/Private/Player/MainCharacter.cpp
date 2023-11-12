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

	m_pSpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	m_pSpringArmComponent->SetupAttachment(GetRootComponent());
	m_pSpringArmComponent->bUsePawnControlRotation = true;
	m_pSpringArmComponent->bInheritYaw = false;

	m_pCameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	m_pCameraComponent->SetupAttachment(m_pSpringArmComponent);

	m_pHealthComponent = CreateDefaultSubobject<UHealthComponent>("HealthComponent");
}


void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();

	check(GetCharacterMovement());
	check(GetMesh());

	m_bFinished = false;
	m_characterSpawnTime = FDateTime::Now();

	SetInputOnGame();

	m_pHealthComponent->OnDeath.AddUObject(this, &AMainCharacter::OnDeath);

	m_pSpringArmComponent->SetRelativeRotation(GetActorRotation());
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
	PlayerInputComponent->BindAction("Quit", IE_Pressed, this, &AMainCharacter::QuitGame);
}

void AMainCharacter::MoveForward(float Amount)
{
	if (!m_bCanMove || !m_pCameraComponent)
		return;
	
	AddMovementInput(m_pCameraComponent->GetForwardVector().GetSafeNormal2D(), Amount);

	SetCharacterDirToVelocityDir();
}

void AMainCharacter::MoveRight(float Amount)
{
	if (!m_bCanMove || !m_pCameraComponent)
		return;
	
	AddMovementInput(m_pCameraComponent->GetRightVector().GetSafeNormal2D(), Amount);

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
	if (!m_bCameraMovement)
		return;
	
	AddControllerPitchInput(Amount * m_cameraSpeedPitchRotation);
}

void AMainCharacter::YawInput(float Amount)
{
	if (!m_bCameraMovement)
		return;
	
	FRotator Rotation = m_pSpringArmComponent->GetRelativeRotation();
	Rotation.Yaw += Amount * m_cameraSpeedYawRotation;

	m_pSpringArmComponent->SetRelativeRotation(Rotation);
}

void AMainCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);

	m_bCanMove = false;
	FTimerHandle LandingTimerHandle;
	GetWorldTimerManager().SetTimer(LandingTimerHandle, this, &AMainCharacter::OnLandingEnd, m_landingDelay, false);
}

void AMainCharacter::OnDeath()
{
	ShowCursor();
	this->m_bCameraMovement = false;
	GetCharacterMovement()->DisableMovement();
	
	EnableMeshPhysics();
}

void AMainCharacter::Destroyed()
{
	m_pHealthComponent->OnDeath.Broadcast();
	
	Super::Destroyed();
}

void AMainCharacter::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	
	if (OtherActor->IsA<AFinishSpace>())
	{
		m_bFinished = true;

		ShowCursor();
		this->m_bCameraMovement = false;
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

void AMainCharacter::SetInputOnGame()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PlayerController->SetInputMode(FInputModeGameOnly());
}

void AMainCharacter::EnableMeshPhysics()
{
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Ignore);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetMesh()->SetSimulatePhysics(true);
}

void AMainCharacter::OnLandingEnd()
{
	m_bCanMove = true;
}

void AMainCharacter::QuitGame()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (!PlayerController)
		return;

	UKismetSystemLibrary::QuitGame(GetWorld(), PlayerController, EQuitPreference::Quit, false);
}
