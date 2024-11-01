// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "F2DVectorInt.h"
#include "Player/PlayerPawn.h"

#include "CPP_Piece.generated.h"

class ACPP_Board;
class UBoxComponent;

UCLASS()
class ALGORITHMS_EXAM_API ACPP_Piece : public AActor
{
	GENERATED_BODY()

	int MaxHealth;

	UPROPERTY()
	ACPP_Board* CurrentBoard;
	
public:	
	// Sets default values for this actor's properties
	ACPP_Piece();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/*
	 * Components
	 */

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Piece")
	UBoxComponent* TriggerBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Piece")
	UStaticMeshComponent* MeshComponent;

	/*
	 * Variables
	 */

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Piece")
	int Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Piece")
	F2DVectorInt BoardPosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Piece")
	TArray<F2DVectorInt> MovementOptions;


	//Player reference, Player who owns the piece
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Piece")
	APlayerPawn* PlayerOwner;

	/*
	 * Functions
	 */

	UFUNCTION(BlueprintCallable, Category = "Piece")
	int Damage(int Value);

	UFUNCTION(BlueprintCallable, Category = "Piece")
	bool MoveTowards(F2DVectorInt Direction);


	UFUNCTION()
	void Onclicked();
};
