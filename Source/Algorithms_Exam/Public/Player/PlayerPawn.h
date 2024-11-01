// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DefaultPawn.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "GameplayTagContainer.h"
#include "PlayerPawn.generated.h"

/**
 * 
 */
UCLASS()
class ALGORITHMS_EXAM_API APlayerPawn : public ADefaultPawn
{
	GENERATED_BODY()

	APlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	UCameraComponent* Camera;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mapping")
	class UInputMappingContext* Imc;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inputs")
	class UInputAction* Wasd;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inputs")
	class UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TotalPieces")
	int32 TotalPieces;

	


	UFUNCTION()
	void PlayerMovement(const FInputActionValue& Value);

	UFUNCTION()
	void CameraLook(const FInputActionValue& Value);

};
