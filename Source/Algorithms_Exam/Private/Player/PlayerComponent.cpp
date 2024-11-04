// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerComponent.h"

#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UPlayerComponent::UPlayerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...


}


// Called when the game starts
void UPlayerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

	
}


// Called every frame
void UPlayerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::Printf(TEXT("%d"),SpawnedPieces.Num()));

}



void UPlayerComponent::RemoveTotalPieces(ACPP_Piece* RemovePiece)
{

	SpawnedPieces.Remove(RemovePiece);

}

bool UPlayerComponent::PieceBelongToPlayer(ACPP_Piece* InterectPiece)
{
	for (ACPP_Piece* Piece : SpawnedPieces)
	{
		if (Piece == InterectPiece)
		{
			return true;
		}


	}

	return false;
}


