// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

	void HandleDestruction();

protected:
	void RotateTurret(FVector LootAtTarget);

	void Fire();
	
private:
	// Evita ter que colocar o #include, mas não se consegue fazer herança
	// Só será necessário declarar no #include do header se for necessitar construir um
	// objeto da classe em questão; se for necessário acessar algum membro da classe ou
	// se for necessário fazer a herança dessa classe.
	// Neste caso, como só é declarado o ponteiro para uso posterior, faz-se o uso da
	// forward declaration, deixando para incluir a classe no .cpp, quando for necessário
	// construir o objeto de fato.
	
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	//USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* CapsuleComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* TurretMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawnPoint;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "User Vars", meta= (AllowPrivateAccess = "true"))
	int32 VisibleAnywherePrivInt = 12;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "User Vars", meta= (AllowPrivateAccess = "true"))
	int32 EditAnywherePrivInt = 12;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<class AProjectile> ProjectileClass; // Variável que faz a ligação entre o BP e a classe C++

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta= (AllowPrivateAccess = "true"))
	class UParticleSystem* DeathParticles;

	UPROPERTY(EditAnywhere, Category = "Combat")
	class USoundBase* DeathSound;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<class UCameraShakeBase> DeathCameraShakeClass;
};