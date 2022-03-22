// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"


// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	this->ObjectIsGrabed = false;
	this->GrabedObject = nullptr;

}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	check(GEngine != nullptr);

	// Display a debug message for five seconds. 
	// The -1 "Key" value argument prevents the message from being updated or refreshed.
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("We are using FPSCharacter."));
	
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (this->ObjectIsGrabed) {
		FVector Loc;
		FRotator rot;
		GetController()->GetPlayerViewPoint(Loc, rot);
		FVector NewLocalisation = Loc +rot.Vector()*200;
		GrabedObject->SetActorLocation(NewLocalisation);
	}
	if (this->bPressedJump) {
		Super::Jump();
	}
	else {
		Super::StopJumping();
	}

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &AMyCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMyCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &AMyCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &AMyCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAction("Grab", IE_Pressed, this,&AMyCharacter::Grab);
	PlayerInputComponent->BindAction("Grab", IE_Released, this, &AMyCharacter::UnGrab);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMyCharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AMyCharacter::StopJumping);
}

// Handles input for moving forward and backward.
void AMyCharacter::MoveForward(float Value) {
	// Find out which way is "forward" and record that the player wants to move that way.
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, Value);
}

// Handles input for moving right and left.
void AMyCharacter::MoveRight(float Value) {
	// Find out which way is "right" and record that the player wants to move that way.
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, Value);
}


void AMyCharacter::Grab() {
	FVector Loc;
	FRotator rot;
	FHitResult result;
	GetController()->GetPlayerViewPoint(Loc, rot);
	FVector start = Loc;
	FVector end= Loc + rot.Vector() *500;
	FCollisionQueryParams collisionquery;
	if (GetWorld()->LineTraceSingleByChannel(result, start, end, ECC_Visibility, collisionquery)) {
		if (!(result.GetActor()->Tags.Contains("Imobile"))) {
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, result.ToString());
			ObjectIsGrabed = true;
			GrabedObject = result.GetActor();
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("GRAB HIT"));
		}
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("GRAB NO HIT"));
	}
	DrawDebugLine(GetWorld(), start, end, FColor::Orange, false, 5.0f);
}

void AMyCharacter::UnGrab() {
	if (ObjectIsGrabed) {
		ObjectIsGrabed = false;
	}
}


void AMyCharacter::Jump() {
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("JUMP"));
	bPressedJump = true;
}

void AMyCharacter::StopJumping() {
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("STOP JUMP"));
	bPressedJump = false;
}
