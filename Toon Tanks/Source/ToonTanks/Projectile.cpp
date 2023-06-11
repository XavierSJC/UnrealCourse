// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/DamageType.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
	ParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle System Component"));
	
	RootComponent = BaseMesh;
	ParticleSystemComponent->SetupAttachment(RootComponent);
	ProjectileMovementComponent->InitialSpeed = 10.f;
	ProjectileMovementComponent->MaxSpeed = 20.f;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	BaseMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnProjectileHit);
	PlaySound(LaunchSound);
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::OnProjectileHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	auto owner = GetOwner();
	if (!owner)
	{
		Destroy();
		return;
	} 

	UDamageType::StaticClass();

	//if other actor aren't 'myself' or my owner
	if (OtherActor && OtherActor != this && OtherActor != owner)
	{
		UGameplayStatics::ApplyDamage(OtherActor, Damage, owner->GetInstigatorController(), this, UDamageType::StaticClass());
		if (HitParticles)
		{
			UGameplayStatics::SpawnEmitterAtLocation(this,
				HitParticles,
				GetActorLocation(),
				GetActorRotation());
		}
		PlaySound(HitSound);

		if (HitCameraShakeClass)
		{
			GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(HitCameraShakeClass);
		}
	}
	Destroy();
}

void AProjectile::PlaySound(USoundBase* sound)
{
	if (sound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, sound, GetActorLocation());
	}
}
