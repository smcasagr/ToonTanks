// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class USoundBase;

UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(VisibleAnywhere, Category = "Movement")
	class UProjectileMovementComponent* ProjectileMovementComponent;

	/*
	 * Parâmetros padrão para esse tipo de função
	 * =================================================================================================================
	 * HitComp: componente que irá atingir (fazer o hitting). No caso, o ProjectileMesh;
	 * OtherActor: O ator que será atingido pelo projétil;
	 * OtherComp: O outro componente que será atingido; se atingir o static mesh component do outro ator,
	 *	então aqui se pasa o static mesh component dele;
	 * NormalImpulse: Simulando a física, a engine irá aplicar um impulso em resposta à colisão. Esse parâmetro irá
	 * representar a magnitude e o impulso;
	 *				   
	 * Hit: Retorno com os resultados do HitResult.
	 */
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(EditAnywhere)
	float Damage = 50.f;

	UPROPERTY(EditAnywhere, Category = "Combat")
	class UParticleSystem* HitParticles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	class UParticleSystemComponent* TrailParticles;

	UPROPERTY(EditAnywhere, Category = "Combat")
	USoundBase* LaunchSound;

	UPROPERTY(EditAnywhere, Category = "Combat")
	USoundBase* HitSound;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<class UCameraShakeBase> HitCameraShakeClass; // Utilizado para o efeito na câmera
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
