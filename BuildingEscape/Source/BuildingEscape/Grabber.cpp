// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "Grabber.h"

//Below macro to just identify that such things would get "modified"
#define OUT 
// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UGrabber::Grab() 
{
	UE_LOG(LogTemp, Warning, TEXT("Grab Pressed"));
	///Line trace here 
	auto HitResult = GetFirstPhysicsBodyInReach();
	auto ComponentToGrab = HitResult.GetComponent();
	auto HitActor = HitResult.GetActor();
	if (HitActor)
	{
		PhysicsHandle->GrabComponentAtLocation(
			ComponentToGrab,
			NAME_None,
			ComponentToGrab->GetOwner()->GetActorLocation());

	}
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab Released"));
	PhysicsHandle->ReleaseComponent();
	//if (PhysicsHandle->GrabbedComponent)
	//{

		
	//}
}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{

	DrawDebugLine(GetWorld(), GetLineTraceStart(), GetLineTraceEnd(),
		FColor(255, 0, 0),
		false,
		0.f,
		0.f,
		10.f);
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		GetLineTraceStart(),
		GetLineTraceEnd(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		FCollisionQueryParams(FName(TEXT("")), false, GetOwner())
	);

	AActor* ActorHit = Hit.GetActor();
	if (ActorHit) {
		UE_LOG(LogTemp, Warning, TEXT("Object hit: %s"), *(ActorHit->GetName()));
	}
	return Hit;
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	FindPhysicsHandleComponent();
	SetupInputComponent();
	// ...

}

///look for attached pyhysics handle
void UGrabber::FindPhysicsHandleComponent()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%s does not have physics handle component"), *GetOwner()->GetName());
	}	
}
///look for attached input component (only appears at run time)
void UGrabber::SetupInputComponent() 
{

	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{  // BInding the Grab function to input key
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s does not have input component"), *GetOwner()->GetName());
	}

}
// Called every frame
void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// if the physics handle is attached
	if (PhysicsHandle->GrabbedComponent)
	{
		// move the object we are holding
		PhysicsHandle->SetTargetLocation(GetLineTraceEnd());
	}
	
}

FVector UGrabber::GetLineTraceStart()
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);

	/*UE_LOG(LogTemp, Warning, TEXT("Position: %s , Rotation : %s"),*PlayerViewPointLocation.ToString(),
	*PlayerViewPointRotation.ToString()
	);*/
	return PlayerViewPointLocation;
	
}

FVector UGrabber::GetLineTraceEnd()
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);

	/*UE_LOG(LogTemp, Warning, TEXT("Position: %s , Rotation : %s"),*PlayerViewPointLocation.ToString(),
	*PlayerViewPointRotation.ToString()
	);*/
	
	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector()*Reach;
	return LineTraceEnd;
}