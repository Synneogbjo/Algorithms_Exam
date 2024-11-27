// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CPP_Card.h"
#include "CPP_CountingSort.generated.h"


UCLASS(BlueprintType, Blueprintable)
class ALGORITHMS_EXAM_API UCPP_CountingSort : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "CountingSort")
	void Sort();

	UFUNCTION(BlueprintCallable, Category = "CountingSort")
	void PrintArray();

	UFUNCTION(BlueprintCallable, Category = "CountingSort")
	void FillHand(ACPP_Card* input);  


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CountingSort")
	TArray<ACPP_Card*> CardsForSorting; 
	
	
};
