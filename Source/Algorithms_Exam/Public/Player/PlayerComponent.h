// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CPP_Piece.h"
#include "Components/ActorComponent.h"
#include "PlayerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ALGORITHMS_EXAM_API UPlayerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	//array that will contain the pieces spawned
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pieces")
	TArray<ACPP_Piece*> SpawnedPieces;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Points")
	int32 Points;

	UFUNCTION()
	void RemoveTotalPieces(ACPP_Piece * RemovePiece);


	//function that checks if the piece the player interacts belongs to him
	UFUNCTION()
	bool PieceBelongToPlayer(ACPP_Piece* InteractPiece);


	UFUNCTION()
	void ActionCost();

};
