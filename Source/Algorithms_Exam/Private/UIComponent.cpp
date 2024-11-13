// Fill out your copyright notice in the Description page of Project Settings.


#include "UIComponent.h"
#include "EndGameWidget.h"
#include "Blueprint/UserWidget.h"

// Sets default values for this component's properties
UUIComponent::UUIComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	
	if (UEndGameWidgetClass)
	{
		CreateUIWidget(UEndGameWidgetClass);
	}

}


// Called when the game starts
void UUIComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	if (!CurrentPlayer)
	{
		APawn* Owner = Cast<APawn>(GetOwner());
		CurrentPlayer = Cast<APlayerController>(Owner->GetController());
	}
	if (UEndGameWidgetClass)
	{
		CreateUIWidget(UEndGameWidgetClass);
	}
}


// Called every frame
void UUIComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

UUserWidget* UUIComponent::CreateUIWidget(TSubclassOf<UEndGameWidget> WidgetClass)
{
	if (WidgetClass) {
		UIInstance = CreateWidget<UEndGameWidget>(GetWorld(), WidgetClass);
		if (UIInstance) {
			UIInstance->AddToViewport();
			
		}
	}
	return UIInstance;
}

void UUIComponent::DisplayWinner(FString NewText)
{
	UIInstance->DisplayWinner(NewText);
}

