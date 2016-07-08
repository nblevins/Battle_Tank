// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

private:
    UPROPERTY(EditAnywhere)
    float CrossHairXLocation = 0.5;
    
    UPROPERTY(EditAnywhere)
    float CrossHairYLocation = 0.33333;
    
    UPROPERTY(EditAnywhere)
    float LineTraceRange = 1000000.f;
    
    ATank* GetControlledTank() const;
    
    virtual void BeginPlay() override;
    
    // Called every frame
    virtual void Tick( float DeltaSeconds ) override;

    //Start the tank moving the barrel so that shot goes to crosshair
    void AimTowardsCrosshair();
    
    bool GetSightRayHitLocation(FVector &HitLocation) const; // HitLocation is an OUT param
    
    bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;
    
    bool GetLookVectorHitLocation(FVector LookDirection, FVector &HitLocation) const;
	
};
