#include "Components/PrimitiveComponent.h"
#include "DrawDebugHelpers.h"
#include "GrabComponent.h"
#include "GravityComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"

/*
 *  GrabberComponent.cpp                      Chris & Ashlee Cruzen
 *  Jame Jam 2022                                        02.13.2022
 *
 *    GrabberComponent gives its actor the ability to grab and move
 *  other objects in the scene.
 */


/*--- Macros ---*/

#define OUT


/*--- Lifecycle Functions ---*/

UGrabComponent::UGrabComponent() {
	PrimaryComponentTick.bCanEverTick = true;
}

void UGrabComponent::BeginPlay() {
	Super::BeginPlay();

	InitializeMemberClasses();
	BindInputActions();
}

void UGrabComponent::TickComponent(
	float DeltaTime,
	ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction
) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Update Player View
	UpdatePlayerView();

	// If Object Grabbed, Update Location
	if (PhysicsHandleComponent && PhysicsHandleComponent->GrabbedComponent) {
		PhysicsHandleComponent->SetTargetLocation(RaycastEndPoint);
	}
}


/*--- Private Functions ---*/

void UGrabComponent::InitializeMemberClasses() {

	// Search Owning Actor for a Specific Component Type (Returns first found!)
	PhysicsHandleComponent = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

	// Null Check PhysicsHandleComponent
	if (!PhysicsHandleComponent) {
		UE_LOG(
			LogTemp,
			Error,
			TEXT("No PhysicsHandleComponent found on Actor %s"),
			*GetOwner()->GetName()
		);
	}
}

void UGrabComponent::BindInputActions() {
	if (InputComponent) {
		InputComponent->BindAction(
			TEXT("Grab"), 
			EInputEvent::IE_Pressed,
			this,
			&UGrabComponent::GrabObject
		);
		InputComponent->BindAction(
			TEXT("Grab"), 
			EInputEvent::IE_Released,
			this,
			&UGrabComponent::ReleaseObject
		);
	}
}

void UGrabComponent::UpdatePlayerView() {

	// Update Player Location/Rotation
	PlayerLocation = FVector();
	FRotator PlayerRotation = FRotator();
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerLocation,
		OUT PlayerRotation
	);

	// Update Raycast End Point 
	RaycastEndPoint = PlayerLocation + PlayerRotation.Vector() * PlayerReach;
}

AActor *UGrabComponent::GetActorInView() {

	// Initialize Raycast Variavbles
	FHitResult RaycastHit;
	FCollisionQueryParams RaycastParams = FCollisionQueryParams(
		FName(TEXT("")), // ???
		false, // Whether to use Visibility Collision
		GetOwner()// Any Actor to ignore? (Player!)
	);

	// Perform Raycast
	GetWorld()->LineTraceSingleByObjectType(
		OUT RaycastHit,
		PlayerLocation,
		RaycastEndPoint,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		RaycastParams
	);

	// Determine if Actor Returned
	if (RaycastHit.GetActor()) {

		// Determine if Actor Has GravityComponent
		UActorComponent *Component = RaycastHit.GetActor()->FindComponentByClass(UGravityComponent::StaticClass());
		if (Component) {

			// Determine if Grabbing Enabled
			UGravityComponent *GravityComponent = Cast<UGravityComponent>(Component);
			if (GravityComponent && GravityComponent->Grabbable) {

				// Return Actor
				return RaycastHit.GetActor();
			}
		}
	}

	// No Actor Found
	return nullptr;
}

void UGrabComponent::GrabObject() {
	AActor * RaycastHitActor = GetActorInView();

	// If Actor Found, Grab
	if (RaycastHitActor) {
		PhysicsHandleComponent->GrabComponentAtLocation(
			Cast<UPrimitiveComponent>(
				RaycastHitActor->GetComponentByClass(UPrimitiveComponent::StaticClass())
			),
			NAME_None,
			RaycastHitActor->GetActorLocation()
		);
	}
}

void UGrabComponent::ReleaseObject() {
	PhysicsHandleComponent->ReleaseComponent();
}