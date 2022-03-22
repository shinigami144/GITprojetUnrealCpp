// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DoorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT2_API UDoorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDoorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void ActivateDoor();
	void StopDoor();
private:
	UPROPERTY(EditAnywhere)
	bool openDoor; // if the door is opening
	float RotationBase;
	UPROPERTY(EditAnywhere)
	float RotationExecuted;
	UPROPERTY(EditAnywhere)
	bool doorOpen; // state of the door
	UPROPERTY(EditAnywhere)
		bool IncreamentZrotationPositif;
		
};
