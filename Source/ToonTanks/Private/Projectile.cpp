// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Camera/CameraShakeBase.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false; // não é necessário chamar a função tick todo o momento

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = ProjectileMesh;
	
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
	ProjectileMovementComponent->InitialSpeed = 1500.f;
	ProjectileMovementComponent->MaxSpeed = 1500.f;

	TrailParticles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Smoke Trail"));
	TrailParticles->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	// Bind da função OnHit no evento ComponentHit
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);

	if (LaunchSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, LaunchSound, GetActorLocation());
	}
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AActor* MyOwner = GetOwner(); // Quem disparou o projétil
	
	if (MyOwner == nullptr)
	{
		// Caso o owner do projétil não exista mais, deletar os projéteis disparados por ele.
		Destroy();
		return;
	}
	
	// auto MyOwnerInstigator = MyOwner->GetInstigatorController(); melhores práticas dizem para não usar o AUTO
	AController* MyOwnerInstigator = MyOwner->GetInstigatorController();
	UClass* DamageTypeClass = UDamageType::StaticClass(); // Utilizado quando não se fará uso de tipos de dano

	// Verifica se o OtherActor não é nulo;
	// se o OtherActor não é o projétil, para não se causar dano;
	// e se o OtherActor não foi quem disparou, para não ocasionar dano a quem disparou o projétil.
	if (OtherActor && OtherActor != this && OtherActor != MyOwner)
	{
		/* O outro ator atingido; dano definido na variável, o instigador, o causador do dano (projétil) e o tipo de dano
		 * Ao executar esta função, o evento dano será aplicado a todas as classes atingidas.
		 * Isso fará a função DamageTaken, da classe HealthComponent, ser chamada.
		*/ 
		UGameplayStatics::ApplyDamage(OtherActor, Damage, MyOwnerInstigator, this, DamageTypeClass);

		if (HitParticles)
		{
			UGameplayStatics::SpawnEmitterAtLocation(this, HitParticles, GetActorLocation(), GetActorRotation()); // fumaça qdo acerta algo	
		}

		if (HitSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
		}

		if (HitCameraShakeClass)
		{
			GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(HitCameraShakeClass);
		}
	}
	Destroy(); // independente de o projétil ter acertado algum alvo, destruir o objeto para n ter um acúmulo deles..
}

