// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"

void ATower::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if(TankRef)
    {
        float distance = FVector::Dist(GetActorLocation(), TankRef->GetActorLocation());
        if (distance <= FireRange)
        {
            RotateTurret(TankRef->GetActorLocation());
        }
    }
}

void ATower::BeginPlay()
{
    Super::BeginPlay();

    TankRef = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
}
