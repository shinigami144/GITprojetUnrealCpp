// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include <Runtime\Engine\Public\DrawDebugHelpers.h>
#include "MyCharacter.generated.h"

UCLASS()
class MYPROJECT2_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

private:
	UPROPERTY()
	bool ObjectIsGrabed;
	UPROPERTY()
	AActor* GrabedObject;
	

public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Jump() override;

	virtual void StopJumping() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// Handles input for moving forward and backward.
	UFUNCTION()
	void MoveForward(float Value);

	// Handles input for moving right and left.
	UFUNCTION()
	void MoveRight(float Value);

	UFUNCTION()
	void Grab();

	UFUNCTION()
	void UnGrab();

	
};
