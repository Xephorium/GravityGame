#include "FpsPlayerCharacter.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "Kismet/GameplayStatics.h"

/*
 *  FpsPlayerCharacter.cpp                     Chris & Ashlee Cruzen
 *  Game Jam 2022                                         02.13.2022
 *
 *    FpsPlayerCharacter is a stripped down version of UE4's default
 *  first person PlayerCharacter and allows us to move around in the
 *  game space.
 */


/*--- Lifecycle Functions ---*/

AFpsPlayerCharacter::AFpsPlayerCharacter() {
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// Set Up CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;
}

void AFpsPlayerCharacter::BeginPlay() {
	Super::BeginPlay();
}


/*--- Input Functions ---*/

void AFpsPlayerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) {
	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &AFpsPlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFpsPlayerCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
}

void AFpsPlayerCharacter::MoveForward(float Value) {
	if (Value != 0.0f) {
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AFpsPlayerCharacter::MoveRight(float Value) {
	if (Value != 0.0f) {
		AddMovementInput(GetActorRightVector(), Value);
	}
}
