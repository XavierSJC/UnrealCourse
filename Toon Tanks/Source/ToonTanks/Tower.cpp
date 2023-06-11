// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

void ATower::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (IsTankInRange())
    {
        RotateTurret(TankRef->GetActorLocation());
    }
}

void ATower::BeginPlay()
{
    Super::BeginPlay();

    TankRef = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

    GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, FireRate, true);
}

void ATower::CheckFireCondition()
{
    if(!TankRef) 
    {
        return;
    }

    if (IsTankInRange() && TankRef->IsAlive)
    {
        Fire();
    }
}

bool ATower::IsTankInRange() const
{
    if (!TankRef)
        return false;

    float distance = FVector::Dist(GetActorLocation(), TankRef->GetActorLocation());
    return (distance <= FireRange);
}

void ATower::HandleDestruction()
{
    Super::HandleDestruction();
    Destroy();
}