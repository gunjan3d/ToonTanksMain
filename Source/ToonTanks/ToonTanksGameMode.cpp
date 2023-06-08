// Fill out your copyright notice in the Description page of Project Settings.

#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"
#include "ToonTanksPlayerController.h"

void AToonTanksGameMode::ActorDied(AActor *DeadActor)
{
    if (DeadActor == Tank)
    {
        Tank->HandleDestruction();
        if (ToonTanksPlayerController)
        {
            ToonTanksPlayerController->SetPlayerEnabledState(false);
        }
        GameOver(false);
    }

    else if (ATower *DestroyedActor = Cast<ATower>(DeadActor))
    {
        DestroyedActor->HandleDestruction();
        TargetTowers--;
        if(TargetTowers == 0)
        {
            GameOver(true);
        }
    }
}

void AToonTanksGameMode::BeginPlay()
{
    Super::BeginPlay();
    HandleGameStart();
}

void AToonTanksGameMode::HandleGameStart()
{
    TargetTowers = GetTowerCount();
    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
    ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
    StartGame();
    if (ToonTanksPlayerController)
    {
        ToonTanksPlayerController->SetPlayerEnabledState(false);

        FTimerHandle PlayerEnabledTimerHandle;
        FTimerDelegate PlayerEnabledTimerDelegate = FTimerDelegate::CreateUObject(
            ToonTanksPlayerController,
            &AToonTanksPlayerController::SetPlayerEnabledState,
            true);
        GetWorldTimerManager().SetTimer(PlayerEnabledTimerHandle, PlayerEnabledTimerDelegate, StartDelay, false);
    }
}
int32 AToonTanksGameMode::GetTowerCount()
{
    TArray<AActor*> Towers;
    UGameplayStatics::GetAllActorsOfClass(this,ATower::StaticClass(),Towers);
    return Towers.Num();
}
