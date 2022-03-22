// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorComponent.h"
#include <Runtime\Engine\Public\DrawDebugHelpers.h>

// Sets default values for this component's properties
UDoorComponent::UDoorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;


	// ...
}


// Called when the game starts
void UDoorComponent::BeginPlay()
{
	Super::BeginPlay();
	this->openDoor = false;
	this->RotationExecuted = 0;
	this->doorOpen = false;
	// ...
	
}


// Called every frame
void UDoorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (this->openDoor) {
		float RotationZ;
		if (this->IncreamentZrotationPositif == true) {
			RotationZ = 1;
		}
		else {
			RotationZ = -1;
		}
		this->RotationExecuted += RotationZ;
		GetOwner()->AddActorLocalRotation(FQuat(FRotator(0, RotationZ, 0)));
		if (this->RotationExecuted >= 90) {
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("90"));
			this->doorOpen = true;
			this->StopDoor();
		}
		else if (this->RotationExecuted <= 0) {
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("0"));
			this->doorOpen = false;
			this->StopDoor();
		}
	}
}

void UDoorComponent::ActivateDoor() {
	if (this->openDoor == true) {
		StopDoor();
	}
	this->openDoor = true;

}

void UDoorComponent::StopDoor() {
	this->openDoor = false;
	this->IncreamentZrotationPositif = !this->IncreamentZrotationPositif;
}

