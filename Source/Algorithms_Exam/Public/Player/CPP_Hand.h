// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CPP_Hand.generated.h"

class UCPP_Stack;
class UCPP_CountingSort;
class ACPP_Card;
/**
 * 
 */
UCLASS()
class ALGORITHMS_EXAM_API UCPP_Hand : public UObject
{
	GENERATED_BODY()

	TArray<UCPP_Stack*> DrawPiles;

	void DrawCard(UCPP_Stack* Stack);

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hand")
	int MaxCards = 8;

	UPROPERTY(BlueprintReadOnly, Category = "Hand")
	TArray<ACPP_Card*> Cards;

	UPROPERTY()
	UCPP_CountingSort* Sorter;

	UFUNCTION(BlueprintCallable, Category = "Hand")
	ACPP_Card* UseCard(int Index);
};
