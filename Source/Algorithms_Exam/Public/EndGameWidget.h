// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "Components/WidgetComponent.h"
#include "Blueprint/UserWidget.h"
#include "EndGameWidget.generated.h"

class UCanvasPanel;


/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class ALGORITHMS_EXAM_API UEndGameWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	//UEndGameWidget(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, Category="EndGameResult")
	void DisplayWinner(FString NewText);  //i can call DisplayWinner(Player1/2) in where the outcome is decided

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category= "EndGameResult")
	FString Winner="";

	UPROPERTY(EditAnywhere, Category = "EndGameResult", meta = (BindWidget))
	UCanvasPanel* Canvas;


};
