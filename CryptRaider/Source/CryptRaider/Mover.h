// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Math/Vector.h"
#include "Mover.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRYPTRAIDER_API UMover : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMover();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void SetShouldMove(bool newShouldMove);

	UFUNCTION(BlueprintCallable)
	void SetShouldRotate(bool ShouldRotate);

private:
	UPROPERTY(EditAnywhere)
	FVector MoveOffset;

	UPROPERTY(EditAnywhere)
	FRotator RotationOffset;
	
	UPROPERTY(EditAnywhere)
	float MoveTime = 4;

	UPROPERTY(EditAnywhere)
	float RotationSpeed = 4;

	//UPROPERTY(EditAnywhere)
	bool ShouldMove = false;
	bool ShouldRotate = false;

	FVector BirthLocation;
	FRotator BirthRotation;

	void Move(float DeltaTime);
	void Return (float DeltaTime);

	void Rotate(float DeltaTime);
};
