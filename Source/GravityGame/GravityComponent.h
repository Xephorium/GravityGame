#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GravityComponent.generated.h"

/*
 *  GravityComponent.h                        Chris & Ashlee Cruzen
 *  Game Jam 2022                                        02.13.2022
 */

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UGravityComponent : public UActorComponent {
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FVector GravityDirection = FVector(0, 0, -978.f);

public:
	UGravityComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(
		float DeltaTime,
		ELevelTick TickType,
		FActorComponentTickFunction* ThisTickFunction
	) override;

		
};
