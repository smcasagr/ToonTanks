// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tower.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATower : public ABasePawn
{
	GENERATED_BODY()
	
public:
	
	virtual void Tick(float DeltaTime) override;

	void HandleDestruction();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	class ATank* Tank;

	UPROPERTY(EditDefaultsOnly, Category = "Tower Atribs")
	float FireRange = 200.f;

	FTimerHandle FireRateTimerHandle;
	float FireRate = 2.f; // 2s de intervalo para cada tiro da torre
	void CheckFireCondition();

	bool InFireRange();
};
