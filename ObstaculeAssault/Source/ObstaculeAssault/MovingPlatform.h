// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingPlatform.generated.h"

UCLASS()
class OBSTACULEASSAULT_API AMovingPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovingPlatform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(EditAnywhere, Category="Moving Platform")
	FVector PlataformVelocity = FVector(100, 0, 0);
	UPROPERTY(EditAnywhere, Category="Moving Platform")
	double MaxDistance = 100;
	UPROPERTY(VisibleAnywhere, Category="Moving Platform")
	double DistanceMoved;
	UPROPERTY(EditAnywhere, Category="Moving Platform")
	FRotator RotationVelocity;

	FVector StartPosition = FVector(1, 2, 3);
	FVector StopPosition = FVector(1, 2, 3);

	void MovePlatform(float DeltaTime);
	void RotatePlatform(float DeltaTime);

	bool ShouldPlatformReturn() const;
	double GetDistanceMoved() const;
};
