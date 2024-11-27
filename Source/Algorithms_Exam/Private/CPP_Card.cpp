// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_Card.h"

#include "Effects/CPP_EffectLocation.h"
#include "Effects/CPP_EffectParent.h"
#include "CPP_Board.h"
#include "Effects/CPP_EffectDamage.h"

// Sets default values
ACPP_Card::ACPP_Card()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CardCost = 0;
	//CardRole = ? ;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	Mesh->SetupAttachment(GetRootComponent());

	CardEffects.Init(nullptr, 9);
}

// Called when the game starts or when spawned
void ACPP_Card::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACPP_Card::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

/// Activates the card, and does all its effects
/// @param PieceLocation Where the piece using the card is located on the board
///	@param bInvertDirection Whether to invert the placement of the effects. Needed when it is Player1's turn
void ACPP_Card::SpawnEffects(F2DVectorInt PieceLocation, bool bInvertDirection)
{
	if (!Board)
	{
		return;
	}

	F2DVectorInt StartLocation(0,0);

	int Modulo = static_cast<int>(sqrt(CardEffects.Num()));

	//Finds the EffectLocation Class type, and saves the index as start location
	for (int i = 0; i < CardEffects.Num(); i++)
	{
		if (CardEffects[i] == ACPP_EffectLocation::StaticClass())
		{
			StartLocation = F2DVectorInt(i % Modulo, static_cast<int>(floor(i / Modulo)));
			break;
		}
	}

	//Spawns all Card Effects on the matching Tile location
	for (int i = 0; i < CardEffects.Num(); i++)
	{
		UClass* EffectClass = CardEffects[i];
		//Skips all Effect Classes that are of the type ACPP_EffectLocation
		if (EffectClass == ACPP_EffectLocation::StaticClass()) continue;

		if (!EffectClass) continue;

		F2DVectorInt SpawnPosition =	F2DVectorInt((Modulo - 1) * bInvertDirection - (i % Modulo), (Modulo - 1) * bInvertDirection - (static_cast<int>(floor(i / Modulo))))
										- StartLocation + PieceLocation;

		FVector SpawnLocation = Board->GetTileAt(SpawnPosition)->GetActorLocation();

		AActor* SpawnedActor = GetWorld()->SpawnActor(EffectClass, &SpawnLocation);

	}
}

