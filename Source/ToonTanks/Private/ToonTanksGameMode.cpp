// Fill out your copyright notice in the Description page of Project Settings.

#include "ToonTanksGameMode.h"

#include "Tank.h"
#include "ToonTanksPlayerController.h"
#include "Tower.h"
#include "Kismet/GameplayStatics.h"

void AToonTanksGameMode::BeginPlay()
{
	Super::BeginPlay();

	HandleGameStart();
}

// Função que cuida dos parâmetros iniciais do jogo, como os ponteiros necessários para consulta
// bem como o delay antes de iniciar, onde o player não conseguirá controlar nada.
void AToonTanksGameMode::HandleGameStart()
{
	TargetTowers = GetTargetTowerCount(); // Inicializa a variável com todas as torres existentes no mundo
	
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0)); // Ref para o player tank
	ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	StartGame(); // Carrega o Evento que será chamado via BP quando inicializar o jogo
	
	if (ToonTanksPlayerController)
	{
		ToonTanksPlayerController->SetPlayerEnabledState(false);

		// inicializa o timer
		FTimerHandle PlayerEnableTimerHandle;
		FTimerDelegate PlayerEnableTimerDelegate =
			FTimerDelegate::CreateUObject(ToonTanksPlayerController,
										  &AToonTanksPlayerController::SetPlayerEnabledState,
										  true);

		GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle,
										 PlayerEnableTimerDelegate,
										 StartDelay,
										 false);

		
	}
	
}

void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{
	if (DeadActor == Tank)
	{
		Tank->HandleDestruction();

		if (ToonTanksPlayerController)
		{
			ToonTanksPlayerController->SetPlayerEnabledState(false);
		}
		GameOver(false);
	}
	// Se conseguir fazer o Cast para ATower, temos uma torre destruída; seus dados estão na var. DestroyedTower
	else if (ATower* DestroyedTower = Cast<ATower>(DeadActor))
	{
		DestroyedTower->HandleDestruction();
		--TargetTowers;

		if (TargetTowers == 0)
		{
			GameOver(true);
		}
	}
}

int32 AToonTanksGameMode::GetTargetTowerCount()
{
	TArray<AActor*> Towers;
	UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), Towers);

	return Towers.Num();
}
