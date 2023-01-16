// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"


UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

public:
	ATank();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void HandleDestruction();

	APlayerController* GetTankPlayerController() const { return TankPlayerController; }

	bool bAlive = true;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
private:

	APlayerController* TankPlayerController;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tank Atribs", meta = (AllowPrivateAccess = "true"))
	float Speed = 200.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tank Atribs", meta = (AllowPrivateAccess = "true"))
	float TurnRate = 40.f;
	
	void Move(float Value);

	void Turn(float Value);
	
};
