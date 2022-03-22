// Fill out your copyright notice in the Description page of Project Settings.


#include "PressionComponent.h"
#include "DoorComponent.h"
#include "MyKeyComponent.h"
#include "Components/BoxComponent.h"
#include <Runtime\Engine\Public\DrawDebugHelpers.h>


// Sets default values for this component's properties
UPressionComponent::UPressionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}


// Called when the game starts
void UPressionComponent::BeginPlay()
{
	Super::BeginPlay();
	Collider = Mesh->FindComponentByClass<UBoxComponent>();
	if (!Collider) {
		return;
	}
	else {
		//Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("UE4MERDE"));
	}
	this->HasTheGoodKey = false;
	Collider->OnComponentBeginOverlap.AddDynamic(this,&UPressionComponent::OnOverlap);
	Collider->OnComponentEndOverlap.AddDynamic(this, &UPressionComponent::OnOverlapEnd);
	// Find 2 object 1 key 1 door
	
}


// Called every frame
void UPressionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// ...
}

void UPressionComponent::OnOverlap(class UPrimitiveComponent* Comp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult){
	if (OtherActor->GetUniqueID() == this->Key->GetUniqueID()) {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("GOOD KEY"));
		this->Door->FindComponentByClass<UDoorComponent>()->ActivateDoor();
		this->HasTheGoodKey = true;
	}
	// if overlap object == Key
	// open door

}

void UPressionComponent::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex){
	if (this->HasTheGoodKey == true) {
		this->Door->FindComponentByClass<UDoorComponent>()->ActivateDoor();
	}
}


