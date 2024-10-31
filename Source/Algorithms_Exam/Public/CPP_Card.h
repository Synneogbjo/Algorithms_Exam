// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FRole.h"
#include "F2DVectorInt.h"
#include "CPP_Card.generated.h"

UCLASS(Blueprintable)
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
	FString CardName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card")
	int32 CardCost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card")
	FRole CardRole;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card")
	TArray<F2DVectorInt> CardActionGrid; //An array containing which direction the card can attack towards

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card")
	TArray<AActor*> CardAttack; //An array containing which type of attack is used

	//UFUNCTION(BlueprintCallable, Category = "Card")
	//void SpawnAttack(const FVector Location, CardAttack);  //FTile instead of location?

};
