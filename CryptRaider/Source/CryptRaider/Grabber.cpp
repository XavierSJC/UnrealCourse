// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UPhysicsHandleComponent* physicsHandle = GetPhysicsHandle();

	//UE_LOG(LogTemp, Display, TEXT("%s: Current rotation <%s>"), *GetOwner()->GetName(), *GetComponentRotation().ToCompactString());
	//UE_LOG(LogTemp, Display, TEXT("%s: Time elipsed <%f>"), *GetOwner()->GetName(), GetWorld()->TimeSeconds);

	//DrawDebugLine(GetWorld(), GetComponentLocation(), End, FColor::Red);

	//Checks if the physicsHandle has a grabbed component
	if (physicsHandle && physicsHandle->GetGrabbedComponent())
	{
		FVector End = GetComponentLocation() + (GetForwardVector() * HoldDistance);
		physicsHandle->SetTargetLocationAndRotation(End, GetComponentRotation());
	}
}

void UGrabber::Grab()
{
	UPhysicsHandleComponent* physicsHandle = GetPhysicsHandle();
	if (physicsHandle == nullptr)
	{
		return;
	}

	FHitResult hitResult;
	if (GetGrabbableInReach(hitResult))
	{
		//DrawDebugSphere(GetWorld(), hitResult.Location, 10, 10, FColor::Blue, false, 5);
		//DrawDebugSphere(GetWorld(), hitResult.ImpactPoint, 10, 10, FColor::Red, false, 5);

		UPrimitiveComponent* hitComponent = hitResult.GetComponent();
		hitComponent->SetSimulatePhysics(true);
		hitComponent->WakeAllRigidBodies();
		
		hitResult.GetActor()->Tags.Add(TagGrabbed);
		hitResult.GetActor()->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

		physicsHandle->GrabComponentAtLocationWithRotation(
			hitComponent,
			NAME_None,
			hitResult.ImpactPoint,
			GetComponentRotation()
		);
	}
}

void UGrabber::Release()
{
	UPhysicsHandleComponent* physicsHandle = GetPhysicsHandle();
	if (physicsHandle == nullptr)
	{
		return;
	}

	UPrimitiveComponent* component = physicsHandle->GetGrabbedComponent();
	if (component)
	{
		component->WakeAllRigidBodies();
		physicsHandle->ReleaseComponent();

		component->GetOwner()->Tags.Remove(TagGrabbed);
	}
	
}

UPhysicsHandleComponent* UGrabber::GetPhysicsHandle() const
{
	UPhysicsHandleComponent* physicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if (physicsHandle == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%s: Not is possibel get component PhysicsHandleComponent"),
				*GetOwner()->GetName());
	}

	return physicsHandle;
}

bool UGrabber::GetGrabbableInReach(FHitResult& HitResult) const
{
	//To get the trace channel, look for the file Config/DefaultEngine.ini
	FVector End = GetComponentLocation() + (GetForwardVector() * MaxGrabDistance);
	FCollisionShape sphere = FCollisionShape::MakeSphere(GrabRadius);
	return GetWorld()->SweepSingleByChannel(
		HitResult, 
		GetComponentLocation(), 
		End, 
		FQuat::Identity, 
		ECC_GameTraceChannel2,
		sphere);
}
