// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Tank.h"
#include "Tower.h"
#include "ToonTanksPlayerController.h"
#include "Kismet/GameplayStatics.h"

void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{
    if (DeadActor == Tank)
    {
        Tank->HandleDestruction();
        if (ToonTanksPlayerController)
        {
            ToonTanksPlayerController->SetPlayerEnabledState(false);
        }

    }
    else if (auto destroyerTower = Cast<ATower>(DeadActor))
    {
        destroyerTower->HandleDestruction();
    }
}

void AToonTanksGameMode::BeginPlay()
{
    Super::BeginPlay();

    HandleGameStart();
}

void AToonTanksGameMode::HandleGameStart()
{
    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
    ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

    if (!ToonTanksPlayerController)
        return;

    ToonTanksPlayerController->SetPlayerEnabledState(false);
    FTimerHandle playerEnableTimerHandle;
    FTimerDelegate playerEnableTimerDelegate =
        FTimerDelegate::CreateUObject(ToonTanksPlayerController, &AToonTanksPlayerController::SetPlayerEnabledState, true);
    GetWorldTimerManager().SetTimer(playerEnableTimerHandle, playerEnableTimerDelegate, StartDelay, false);
    
}