#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FpsPlayerCharacter.generated.h"

/*
 *  FpsPlayerCharacter.h                       Chris & Ashlee Cruzen
 *  Game Jam 2022                                         02.13.2022
 */

class UInputComponent;
class UCameraComponent;

UCLASS(config=Game)
class AFpsPlayerCharacter : public ACharacter {
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

public:
	AFpsPlayerCharacter();

protected:
	virtual void BeginPlay();

protected:
	void MoveForward(float Val);
	void MoveRight(float Val);
	
protected:
	// From APawn Fnterface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

public:
	UCameraComponent* GetFirstPersonCameraComponent() const {
		return FirstPersonCameraComponent;
	}

};

