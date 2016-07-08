// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"



void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay();
    
    ATank* ControlledTank = GetControlledTank();
    
    if (!ControlledTank) {
        UE_LOG(LogTemp, Warning, TEXT("No Tank Possesed"));
    } else {
        FString Name = ControlledTank->GetName();
        UE_LOG(LogTemp, Warning, TEXT("The Posessed  Player Tank is named : %s"), *Name);
    }
    
}


// Called every frame
void ATankPlayerController::Tick( float DeltaTime )
{
    Super::Tick( DeltaTime );
    
    AimTowardsCrosshair();
}


ATank* ATankPlayerController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
    
}

void ATankPlayerController::AimTowardsCrosshair()
{
    if (!GetControlledTank()){return;}
    
    FVector HitLocation; // OUT parameter
    
    GetSightRayHitLocation(HitLocation);
    
    //UE_LOG(LogTemp, Warning, TEXT("Hit Location passed back: %s"), *HitLocation.ToString());
    
    
    //Get world location if linetrace through crosshair
    
}

bool ATankPlayerController::GetSightRayHitLocation(FVector &HitLocation) const // HitLocation is an OUT param
{
    int32 ViewportSizeX, ViewportSizeY;
    GetViewportSize(ViewportSizeX, ViewportSizeY);
    
    auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);
  
    FVector LookDirection;
    
    if (GetLookDirection(ScreenLocation, LookDirection)) {
        UE_LOG(LogTemp, Warning, TEXT("Direction: %s"), *LookDirection.ToString())
    }
    
    return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
    FVector CameraLocation; // to be discarded
    
    return (DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraLocation, LookDirection));
    
}