// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ATank::ATank()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm Component"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	Camera->SetupAttachment(SpringArm);
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);
	
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATank::Fire);
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (TankPlayerController)
	{
		FHitResult HitResult;
		TankPlayerController->GetHitResultUnderCursor(
			ECollisionChannel::ECC_Visibility,
			false,
			HitResult);
		
		/*
		DrawDebugSphere(
			GetWorld(),
			HitResult.ImpactPoint, // onde esfera irá aparecer
			20.f, // tamanho da esfera (raio)
			12,
			FColor::Red,
			false,
			-1.f);
		*/

		RotateTurret(HitResult.ImpactPoint);
	}
}

void ATank::HandleDestruction()
{
	Super::HandleDestruction();
	SetActorHiddenInGame(true); // Não deleta o obj tanque, mas o esconde, no intuito de manter a câmera.
	SetActorTickEnabled(false); // como o tanque foi destruído, desabilida a Tick function dele.
	bAlive = false;
}


// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

	TankPlayerController = Cast<APlayerController>(GetController());
}

void ATank::Move(float Value)
{
    // Valor do parâmetro Value é setado pelo axis binding configurado nas inputs da engine

	FVector DeltaLocation = FVector::ZeroVector;
	// X = Value * DeltaTime * Speed
	float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this); // Busca o valor do DeltaTime desse objeto
	DeltaLocation.X = Value * Speed * DeltaTime;
	AddActorLocalOffset(DeltaLocation, true);
}

void ATank::Turn(float Value)
{
	FRotator DeltaRotation = FRotator::ZeroRotator;
	// Yaw = Value * DeltaTime * TurnRate
	float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this); // Busca o valor do DeltaTime desse objeto
	DeltaRotation.Yaw = Value * DeltaTime * TurnRate;
	AddActorLocalRotation(DeltaRotation, true);
}