#include "FpsPlayerCharacter.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "GrabComponent.h"
#include "GravityComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

/*
 *  FpsPlayerCharacter.cpp                     Chris & Ashlee Cruzen
 *  Game Jam 2022                                         02.13.2022
 *
 *    FpsPlayerCharacter is a stripped down version of UE4's default
 *  first person PlayerCharacter and allows us to move around in the
 *  game space.
 */


/*--- Macros ---*/

#define OUT


/*--- Lifecycle Functions ---*/

AFpsPlayerCharacter::AFpsPlayerCharacter() {
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// Set Up CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Set Up GrabComponent
	UPhysicsHandleComponent *PhysicsComponent = CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("Physics Component"));
	this->AddOwnedComponent(PhysicsComponent);
	UGrabComponent *GrabComponent = CreateDefaultSubobject<UGrabComponent>(TEXT("Grab Component"));
	this->AddOwnedComponent(GrabComponent);
}

void AFpsPlayerCharacter::BeginPlay() {
	Super::BeginPlay();
}


/*--- Input Functions ---*/

void AFpsPlayerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) {
	check(PlayerInputComponent);

	// Basic Movement
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAxis("MoveForward", this, &AFpsPlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFpsPlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	// Gravity
	PlayerInputComponent->BindAction("ToggleZGravity", IE_Pressed, this, &AFpsPlayerCharacter::ToggleZGravity);
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

void AFpsPlayerCharacter::ToggleZGravity() {
	GravityDirectionZ *= -1.f;
	UpdateSceneGravity();
}

void AFpsPlayerCharacter::UpdateSceneGravity() {

	// Get All Actors in Scene
	TArray<AActor*> ActorsInScene;
	UGameplayStatics::GetAllActorsOfClass(
		GetWorld(),
		AActor::StaticClass(),
		OUT ActorsInScene
	);

	for (AActor *Actor: ActorsInScene) {

		// If Actor Has Gravity Component
		UActorComponent *Component = Actor->FindComponentByClass(UGravityComponent::StaticClass());
		if (Component) {

			// Set Gravity
			UGravityComponent *GravityComponent = Cast<UGravityComponent>(Component);
			GravityComponent->GravityDirection = FVector(0.f, 0.f, GravityDirectionZ * 978.f);
		}
	}
}