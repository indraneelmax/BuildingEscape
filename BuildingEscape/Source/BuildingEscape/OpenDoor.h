// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();
	void OpenDoor();
	void CloseDoor();
	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;
	float GetTotalMassOfActorsOnPlate();
	///below is our custom event definition on open door
	///what happens is handled in door blueprint
	///e.g for C++ & Blueprint communication
	UPROPERTY(BlueprintAssignable)
		FDoorEvent OnOpen;
	
	UPROPERTY(BlueprintAssignable)
		FDoorEvent OnClose;
private:
	UPROPERTY(EditAnywhere)
		ATriggerVolume* PressurePlate = nullptr;

	float LastOpenDoorTime;
	AActor *Owner = nullptr;
	
	float TriggerMass = 30.f;
	//UPROPERTY(EditAnywhere)
	AActor* ActorThatOpens;

};
