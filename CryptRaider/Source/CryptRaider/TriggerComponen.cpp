// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponen.h"

// Sets default values for this component's properties
UTriggerComponen::UTriggerComponen()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}

// Called when the game starts
void UTriggerComponen::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void UTriggerComponen::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!Mover)
	{
		return;
	}
	
	auto actor = GetAcceptableActor();
	if (actor)
	{
		//UE_LOG(LogTemp, Display, TEXT("Actor overlopping <%s>"), *actor->GetActorNameOrLabel()); 

		UPrimitiveComponent* component = Cast<UPrimitiveComponent>(actor->GetRootComponent());
		if (component)
		{
			component->SetSimulatePhysics(false);
		}
		actor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
		Mover->SetShouldMove(true);
		Mover->SetShouldRotate(true);
	}
	else
	{
		//UE_LOG(LogTemp, Display, TEXT("No actor overlopping")); 
		Mover->SetShouldMove(false);
		Mover->SetShouldRotate(false);
	}
}

AActor* UTriggerComponen::GetAcceptableActor() const
{
	TArray<AActor*> actors;
	GetOverlappingActors(actors);

	/*
	for (int32 index = 0; index < actors.Num(); index++)	
	{
		UE_LOG(LogTemp, Display, TEXT("First actor overlopping <%s>"), *actors[0]->GetActorNameOrLabel()); 
	}
	*/
	for (AActor* actor : actors)
	{
		if (actor->ActorHasTag(TriggerTag) && !actor->ActorHasTag("Grabbed"))
		{
			return actor;
		}
	}

	return nullptr;
}

void UTriggerComponen::SetMover(UMover* mover)
{
	Mover = mover;
}