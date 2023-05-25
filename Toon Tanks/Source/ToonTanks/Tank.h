// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

public:
	ATank();

	// Called to bind functionality to input
	void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Moviment", meta = (AllowPrivateAccess = "true"))
	float Speed = 200.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Moviment", meta = (AllowPrivateAccess = "true"))
	float TurnRate = 10.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, category = "Camera", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, category = "Camera", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent;

	void Move(float Value);
	void Turn(float Value);
};
