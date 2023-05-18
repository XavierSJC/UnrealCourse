// Fill out your copyright notice in the Description page of Project Settings.


#include "Mover.h"
#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
UMover::UMover()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMover::BeginPlay()
{
	Super::BeginPlay();
	BirthLocation = GetOwner()->GetActorLocation();
	BirthRotation = GetOwner()->GetActorRotation();
}


// Called every frame
void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (ShouldMove)
	{
		Move(DeltaTime);
	}
	else
	{
		Return(DeltaTime);
	}

	if (ShouldRotate)
	{
		Rotate(DeltaTime);
	}
}

void UMover::Move(float DeltaTime)
{
	FVector targetLocation = BirthLocation + MoveOffset;
	float speed = FVector::Distance(BirthLocation, targetLocation)/MoveTime;

	FVector newLocation = FMath::VInterpConstantTo(GetOwner()->GetActorLocation(), targetLocation, DeltaTime, speed);

	GetOwner()->SetActorLocation(newLocation);
}

void UMover::Return(float DeltaTime)
{
	FVector targetLocation = BirthLocation;
	float speed = FVector::Distance(BirthLocation + MoveOffset, BirthLocation)/MoveTime;

	FVector newLocation = FMath::VInterpConstantTo(GetOwner()->GetActorLocation(), targetLocation, DeltaTime, speed);

	GetOwner()->SetActorLocation(newLocation);
}

void UMover::SetShouldMove(bool newShouldMove)
{
	ShouldMove = newShouldMove;
}

void UMover::SetShouldRotate(bool shouldRotate)
{
	ShouldRotate = shouldRotate;
}

void UMover::Rotate(float DeltaTime)
{	
	FRotator targetRotation = BirthRotation + RotationOffset;

	FRotator newRotation = FMath::RInterpConstantTo(GetOwner()->GetActorRotation(), targetRotation, DeltaTime, RotationSpeed);
	
	GetOwner()->SetActorRotation(newRotation);
}