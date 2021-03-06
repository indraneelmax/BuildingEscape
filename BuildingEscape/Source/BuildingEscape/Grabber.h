// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	void SetupInputComponent();
	void FindPhysicsHandleComponent();
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

private:
	float Reach = 100.0f;
	UPhysicsHandleComponent* PhysicsHandle = nullptr;

	UInputComponent* InputComponent = nullptr;
	void Grab();
	void Release();
	//Return hit for the first physics body in reach
	const FHitResult GetFirstPhysicsBodyInReach();
	///Get the start/origin of player/pawn from where to Reach for Grab
	FVector GetLineTraceStart();
	/// Get the end of reach for Grab
	FVector GetLineTraceEnd();


};


