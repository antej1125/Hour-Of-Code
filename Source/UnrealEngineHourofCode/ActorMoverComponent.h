// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ActorMoverComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALENGINEHOUROFCODE_API UActorMoverComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;	// Called every frame

	UActorMoverComponent();	// Sets default values for this component's properties

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement")
	FVector EndPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement")
	float Speed;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	FVector MovementDirection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float DistanceToMove;


private:
	bool bMovingForward;
	float CurrentLerpTime;
	FVector StartLocation;
};