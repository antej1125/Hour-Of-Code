// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorMoverComponent.h"
#include "Math/Vector.h"
#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
UActorMoverComponent::UActorMoverComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	Speed = 500.0f;
	bMovingForward = true;


	CurrentLerpTime = 0.0f;
}

// Called when the game starts
void UActorMoverComponent::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetOwner()->GetActorLocation();
	DistanceToMove = FVector::Distance(StartLocation, EndPoint);
}


// Called every frame
void UActorMoverComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
   Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

   FVector CurrentLocation = GetOwner()->GetActorLocation();
   float DistanceToTarget = FVector::Distance(CurrentLocation, EndPoint);
   float LerpDistance = DistanceToMove / 6.0f;
   float PlatformSpeed;
   float SlowSpeed = Speed / 8.0f;
   float alpha = LerpDistance / DistanceToMove;

   if ((FVector::Distance(CurrentLocation, EndPoint) >= LerpDistance) ||
      (FVector::Distance(CurrentLocation, StartLocation) <= LerpDistance))
   {
      PlatformSpeed = FMath::Lerp(Speed, SlowSpeed, alpha);
   }
   else
   {
      PlatformSpeed = FMath::Lerp(SlowSpeed, Speed, alpha); 
   }
   
   if (DistanceToTarget < 1.0f) // end point
   {
      FVector TempLocation = StartLocation;
      StartLocation = EndPoint;
      EndPoint = TempLocation;
   }

   MovementDirection = (EndPoint - StartLocation).GetSafeNormal();

   // Check, moving forward or back
   if (bMovingForward)
   {
      FVector NewLocation = CurrentLocation + MovementDirection * PlatformSpeed * DeltaTime;    // Calculate new pos in forward
      GetOwner()->SetActorLocation(NewLocation);   // move actor to new pos

      // Checking if we have reached the starting point
      if (FVector::Distance(NewLocation, StartLocation) >= FVector::Distance(StartLocation, EndPoint))
      {
         bMovingForward = false; // Change Direction
      }
   }
   else
   {
      FVector NewLocation = CurrentLocation - MovementDirection * PlatformSpeed * DeltaTime;  // Calculate new position back
      GetOwner()->SetActorLocation(NewLocation);   // move actor to new pos

      // Checking if we have reached the end point
      if (FVector::Distance(NewLocation, EndPoint) >= FVector::Distance(StartLocation, EndPoint))
      {
         bMovingForward = true; // Change Direction
      }
   }
}
