#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/InputComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "GrabComponent.generated.h"

/*
 *  GrabberComponent.h                        Chris & Ashlee Cruzen
 *  Jame Jam 2022                                        02.13.2022
 */

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UGrabComponent : public UActorComponent {
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	float PlayerReach = 250.f;

private:
	UPhysicsHandleComponent *PhysicsHandleComponent = nullptr;
	UInputComponent *InputComponent = nullptr;
	FVector PlayerLocation;
	FVector RaycastEndPoint;

public:	
	UGrabComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(
		float DeltaTime,
		ELevelTick TickType,
		FActorComponentTickFunction* ThisTickFunction
	) override;
		
private:
	void InitializeMemberClasses();
	void BindInputActions();

	void UpdatePlayerView();
	AActor *GetActorInView();
	
	void GrabObject();
	void ReleaseObject();
};
