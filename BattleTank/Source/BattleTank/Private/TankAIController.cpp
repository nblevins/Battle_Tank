// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAIController.h"



void ATankAIController::BeginPlay()
{
    Super::BeginPlay();
    
    ATank* ControlledTank = GetControlledTank();
    if (!ControlledTank) {
        UE_LOG(LogTemp, Warning, TEXT("No Tank Possesed"));
    } else {
        FString Name = ControlledTank->GetName();
        UE_LOG(LogTemp, Warning, TEXT("Tank AI controller possessing tank named : %s"), *Name);
    }
    
    ATank* PlayerTank = GetPlayerTank();
    if (!PlayerTank) {
        UE_LOG(LogTemp, Warning, TEXT("No Player Tank Possesed"));
    } else {
        UE_LOG(LogTemp, Warning, TEXT("Tank AI controller found player tank named : %s"), *(PlayerTank->GetName()));
    }

}

// Called every frame
void ATankAIController::Tick( float DeltaTime )
{
    Super::Tick( DeltaTime );
    
    if (GetPlayerTank())
    {
        // Move towards player
        
        //Aim at player's tank
        FVector AimLocation = GetPlayerTank()->GetActorLocation();
        
        if (GetControlledTank()) {
            GetControlledTank()->AimAt(AimLocation);
        }
        
    }

}


ATank* ATankAIController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
    
}

ATank* ATankAIController::GetPlayerTank() const
{
    auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
    if (!PlayerPawn) {return nullptr;}
    return Cast<ATank>(PlayerPawn);
    
}


