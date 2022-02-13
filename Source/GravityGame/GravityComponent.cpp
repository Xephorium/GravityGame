#include "Components/PrimitiveComponent.h"
#include "GameFramework/Actor.h"
#include "GravityComponent.h"

/*
 *  GravityComponent.cpp                      Chris & Ashlee Cruzen
 *  Game Jam 2022                                        02.13.2022
 *
 *    GravityComponent implements custom gravity for the actors its
 *  attached to, with a public direction field that can be used to
 *  change physics behavior in real-time.
 */


/*--- Lifecycle Functions ---*/

UGravityComponent::UGravityComponent() {
	PrimaryComponentTick.bCanEverTick = true;
}

void UGravityComponent::BeginPlay() {
	Super::BeginPlay();	
}

void UGravityComponent::TickComponent(
	float DeltaTime,
	ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction
) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UPrimitiveComponent *OwnerPrimitiveComponent = Cast<UPrimitiveComponent>(
		GetOwner()->GetComponentByClass(UPrimitiveComponent::StaticClass())
	);

	OwnerPrimitiveComponent->AddForce(
		GravityDirection,
		NAME_None,
		true
	);
}

