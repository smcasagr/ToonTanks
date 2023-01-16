// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (InFireRange())
	{
		// if in range, rotate turret toward tank
		RotateTurret(Tank->GetActorLocation());
	}
}

void ATower::HandleDestruction()
{
	Super::HandleDestruction(); // Chama a função da classe BasePawn
	Destroy();
}


void ATower::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

	// timer que irá controlar os disparos do canhão da torre
	GetWorldTimerManager().SetTimer(
		FireRateTimerHandle,
		this,
		&ATower::CheckFireCondition,
		FireRate,
		true);
}

void ATower::CheckFireCondition()
{
	if (Tank == nullptr)
	{
		return;
	}
	
	if (InFireRange() && Tank->bAlive)
	{
		// if in range, FIRE!
		Fire();
	}	
}

bool ATower::InFireRange()
{
	if (Tank)
	{
		// find the distance to the tank
		float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());

		// check to see if the tank is in range
		if (Distance <= FireRange)
		{
			// if in range, return true
			return true;
		}
	}

	return false;
}

