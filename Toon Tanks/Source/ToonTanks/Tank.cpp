// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"

ATank::ATank()
{
    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

    SpringArmComponent->SetupAttachment(RootComponent);
    CameraComponent->SetupAttachment(SpringArmComponent);
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
}

void ATank::Move(float Value)
{
    FVector deltaLocation = FVector::ZeroVector;

    UGameplayStatics::GetWorldDeltaSeconds(this);
    deltaLocation.X = Value * UGameplayStatics::GetWorldDeltaSeconds(this) * Speed;
    AddActorLocalOffset(deltaLocation);
}

