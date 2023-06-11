// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

ATank::ATank()
{
    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

    SpringArmComponent->SetupAttachment(TurretMesh);
    CameraComponent->SetupAttachment(SpringArmComponent);
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
    PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);

    PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATank::Fire);
}

void ATank::Move(float Value)
{
    FVector deltaLocation = FVector::ZeroVector;

    UGameplayStatics::GetWorldDeltaSeconds(this);
    deltaLocation.X = Value * UGameplayStatics::GetWorldDeltaSeconds(this) * Speed;
    AddActorLocalOffset(deltaLocation, true);
}

void ATank::Turn(float Value)
{
    FRotator deltaRotator = FRotator::ZeroRotator;
    deltaRotator.Yaw = Value * UGameplayStatics::GetWorldDeltaSeconds(this) * TurnRate;
    AddActorLocalRotation(deltaRotator, true);
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
    TankPlayerController = Cast<APlayerController>(GetController());
}

void ATank::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (TankPlayerController)
    {
        FHitResult hitResult;
        
        if(TankPlayerController->GetHitResultUnderCursor(
            ECollisionChannel::ECC_Visibility, 
            false, 
            hitResult))
            {
                /*
                DrawDebugSphere(
                    GetWorld(),
                    hitResult.ImpactPoint,
                    15.f,
                    20,
                    FColor::Red
                );
                */
                RotateTurret(hitResult.ImpactPoint);
            }
    }
}

void ATank::HandleDestruction()
{
    Super::HandleDestruction();
    SetActorHiddenInGame(true);
    SetActorTickEnabled(false);
    IsAlive = false;
}

APlayerController* ATank::GetTankPlayerController() const
{
    return TankPlayerController;
}