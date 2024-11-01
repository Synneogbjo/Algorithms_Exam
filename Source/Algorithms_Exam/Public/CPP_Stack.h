// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h" 
#include "CPP_Stacks_Interface.h"
#include "UObject/NoExportTypes.h"
#include "CPP_Stack.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class ALGORITHMS_EXAM_API UCPP_Stack : public UObject, public ICPP_Stacks_Interface
{
	GENERATED_BODY()

	
	UFUNCTION(BlueprintCallable, Category = "Stack")
	virtual void Push_Implementation(ACPP_Card* Card) override;

	UFUNCTION(BlueprintCallable, Category = "Stack")
	virtual ACPP_Card* Pop_Implementation() override;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<ACPP_Card*> CardsArray;
	
};
