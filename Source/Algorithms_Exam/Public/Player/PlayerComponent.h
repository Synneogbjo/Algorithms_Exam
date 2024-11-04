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


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TotalPieces")
	int32 TotalPieces;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pieces")
	TArray<AActor*> SpawnPoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pieces")
	TArray<TSubclassOf<ACPP_Piece>> Pieces;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pieces")
	TArray<ACPP_Piece*> SpawnedPieces;

	UFUNCTION()
	void SpawnPieces();

	UFUNCTION()
	void RemoveTotalPieces();
		
};
