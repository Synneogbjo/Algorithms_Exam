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

	TotalPieces = 0;

}


// Called when the game starts
void UPlayerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

	SpawnPieces();
	
}


// Called every frame
void UPlayerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPlayerComponent::SpawnPieces()
{

	for (AActor* SpawnPoint : SpawnPoints)
	{
		if (SpawnPoint)
		{
			FVector SpawnLocation = SpawnPoint->GetActorLocation();

			for (TSubclassOf<ACPP_Piece> Piece : Pieces)
			{
				if (IsValid(Piece))
				{
					ACPP_Piece* SpawnedPiece = GetWorld()->SpawnActor<ACPP_Piece>(Piece, SpawnLocation, FRotator::ZeroRotator);

					SpawnedPieces.Emplace(SpawnedPiece);
				}

			}
			

		}


	}

}

void UPlayerComponent::RemoveTotalPieces()
{

	TotalPieces--;

}

