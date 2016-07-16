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
    
    if (GetSightRayHitLocation(HitLocation))
    {
        GetControlledTank()->AimAt(HitLocation);
    }
    
    
    
}

bool ATankPlayerController::GetSightRayHitLocation(FVector &HitLocation) const // HitLocation is an OUT param
{
    int32 ViewportSizeX, ViewportSizeY;
    GetViewportSize(ViewportSizeX, ViewportSizeY);
    
    auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);
  
    FVector LookDirection;
    
    if (GetLookDirection(ScreenLocation, LookDirection)) {

        if (GetLookVectorHitLocation(LookDirection, HitLocation)) {
            
           // UE_LOG(LogTemp, Warning, TEXT("Location: %s"), *HitLocation.ToString())

        }
    }
    
    return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
    FVector CameraLocation; // to be discarded
    
    return (DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraLocation, LookDirection));
    
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector &HitLocation) const
{
    //LineTraceSingleByChanel;
    //LineTraceRange
    
    FHitResult OutHit;
    
    auto Start = PlayerCameraManager->GetCameraLocation();
    
    FVector End = Start + (LookDirection * LineTraceRange);
    
    ECollisionChannel TraceChannel = ECC_Visibility;
    
    FCollisionQueryParams Params;
    
    FCollisionResponseParams ResponseParam;
    
    if (GetWorld()->LineTraceSingleByChannel(
                                             OutHit,
                                             Start,
                                             End,
                                             TraceChannel))
        {
            HitLocation = OutHit.Location;
            
            return true;
            
        }
    
    HitLocation = FVector (0);
    
    return false;
    
}







