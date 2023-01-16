// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOONTANKS_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere)
	float MaxHealth = 100.f;
	float Health = 0.f;

	class AToonTanksGameMode* ToonTanksGameMode; // Utilizado para chamar o ActorDied qdo Health chegar a 0.

	/*
	 * Parâmetros padrão para esse tipo de função
	 * =================================================================================================================*
	 * DamagedActor: O Ator que irá levar o dano;
	 * Damage: A quantidade de dano a ser infligida;
	 * DamageType: A Unreal trabalha com conceitos de tipos de dano, onde se pode criar tipos personalizados, que têm
	 *	dados extras, como dano de veneno, dano de fogo, dano de explosão, etc;
	 * Instigator: Responsável pelo dano (player ou outro instigator);
	 * DamageCauser: Ator que provocou o dano.
	 */
	UFUNCTION()
	void DamageTaken(AActor* DamagedActor, float Damage,
		const UDamageType* DamageType, AController* Instigator, AActor* DamageCauser);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
};
