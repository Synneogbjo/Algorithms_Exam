// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CPP_Piece.h"
#include "PlayerPawn.h"
#include "GameFramework/Actor.h"
#include "PieceSpawner.generated.h"


UCLASS()
class ALGORITHMS_EXAM_API APieceSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APieceSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pieces")
	TArray<AActor*> SpawnPoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pieces")
	TArray<TSubclassOf<ACPP_Piece>> Pieces;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	TSubclassOf<APlayerPawn> Player;

	UFUNCTION()
	void SpawnPieces();

	UFUNCTION()
	void AssignPlayer(ACPP_Piece* Piece);

};
