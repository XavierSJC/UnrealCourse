// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	StartPosition = GetActorLocation();

	FString myString = GetName();

	UE_LOG(LogTemp, Display, TEXT("BeginPlayer: <%s>"), *myString);
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MovePlatform(DeltaTime);
	RotatePlatform(DeltaTime);
}

void AMovingPlatform::MovePlatform(float DeltaTime)
{
	if (ShouldPlatformReturn())
	{
		//Check the overshot
		UE_LOG(LogTemp, Display, TEXT("The overshot to player <%s> is:  %f")
			, *GetName()
			, (DistanceMoved - MaxDistance));
		//Resolve issue with platform moving beyind the limit
		FVector MoveDirecion = PlataformVelocity.GetSafeNormal();
		StartPosition += (MoveDirecion * DistanceMoved);
		SetActorLocation(StartPosition);
		//Plataform Returns
		PlataformVelocity = -PlataformVelocity;
	}
	else
	{
		FVector currentLocation = GetActorLocation();
		//Normalize speed to any computer
		currentLocation += (PlataformVelocity * DeltaTime);
		SetActorLocation(currentLocation);
	}
	DistanceMoved = FVector::Dist(StartPosition, GetActorLocation());
}

void AMovingPlatform::RotatePlatform(float DeltaTime)
{
	AddActorLocalRotation(RotationVelocity * DeltaTime);
}

bool AMovingPlatform::ShouldPlatformReturn() const
{
	return GetDistanceMoved() > MaxDistance;
}

double AMovingPlatform::GetDistanceMoved() const
{
	return FVector::Dist(StartPosition, GetActorLocation());
}