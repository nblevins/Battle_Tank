// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"



void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay();
    
    UE_LOG(LogTemp, Warning, TEXT("Beginning play..."));
    
    ATank* ControlledTank = GetControlledTank();
    
    if (!ControlledTank) {
        UE_LOG(LogTemp, Warning, TEXT("No Tank Possesed"));
    } else {
        UE_LOG(LogTemp, Warning, TEXT("There is a Tank Possesed"));
        FString Name = ControlledTank->GetName();
        UE_LOG(LogTemp, Warning, TEXT("The Posessed Tank is named : %s"), *Name);
    }
    
}

ATank* ATankPlayerController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
    
}
