// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FRole.h"
#include "F2DVectorInt.h"

#include "CPP_Card.generated.h"

class ACPP_Board;
class ACPP_EffectParent;

UCLASS(BlueprintType,Blueprintable)
class ALGORITHMS_EXAM_API ACPP_Card : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	ACPP_Card();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card")
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card")
	FString CardName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card")
	int32 CardCost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card")
	FRole CardRole;

	UPROPERTY(EditFixedSize, EditAnywhere, BlueprintReadWrite, Category = "Card")
	TArray<TSubclassOf<ACPP_EffectParent>> CardEffects; //An array containing which type of attack is used

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card")
	ACPP_Board* Board;

	UFUNCTION(BlueprintCallable, Category = "Card")
	void SpawnEffects(F2DVectorInt PieceLocation, bool bInvertDirection);  //FTile instead of location?

};
