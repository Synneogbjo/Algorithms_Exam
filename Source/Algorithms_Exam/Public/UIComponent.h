// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UIComponent.generated.h"

class UUserWidget;
class UEndGameWidget;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ALGORITHMS_EXAM_API UUIComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UUIComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UEndGameWidget> UEndGameWidgetClass;

	UUserWidget* CreateUIWidget(TSubclassOf<UEndGameWidget> WidgetClass);

	UFUNCTION(BlueprintCallable, Category = "UI")
	UEndGameWidget* GetUIWidget() { return UIInstance; }

	UPROPERTY()
	UEndGameWidget* UIInstance;

	UPROPERTY()
	APlayerController* CurrentPlayer;

	UFUNCTION(BlueprintCallable, Category = "EndGameResult")
	void DisplayWinner(FString NewText);  //i can call DisplayWinner(Player1/2) in where the outcome is decided

};

