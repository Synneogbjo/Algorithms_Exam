// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_Piece.h"

#include "CPP_Board.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"

#include "Player/PlayerComponent.h"
#include "Player/PlayerPawn.h"

// Sets default values
ACPP_Piece::ACPP_Piece()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	SetRootComponent(TriggerBox);

	MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	MeshComponent->SetupAttachment(GetRootComponent());



	/*
	 * Variable Initialization
	 */

	CurrentBoard = Cast<ACPP_Board>(UGameplayStatics::GetActorOfClass(this, ACPP_Board::StaticClass()));

	MaxHealth = Health = 4;
	BoardPosition = F2DVectorInt(-1, -1);
	MovementOptions = TArray<F2DVectorInt>();

	

}

// Called when the game starts or when spawned
void ACPP_Piece::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACPP_Piece::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

/// <summary>
/// Changes the Health of this Piece by the Value inserted. Positive Values will do damage, Negative Values will heal.
/// </summary>
/// <param name="Value"> Damage to deal </param>
/// <returns> Current Health after dealing Damage </returns>
int ACPP_Piece::Damage(int Value)
{
	if ((Health - Value) >= MaxHealth)
	{
		Health = MaxHealth;
	}
	else
	{
		Health -= Value;
		if (Health <= 0)
		{

			DestroyPiece();

		}

	}

	return Health;
}

/// <summary>
/// Tries to move this Piece to another Tile based on the Direction inserted. Will only move if the inserted Direction is a legal move for this Piece, and the target Tile is not occupied.
/// </summary>
/// <param name="Direction"> Where to move this Piece to relative to its current location</param>
/// <returns> Could the Piece move to the desired location </returns>
bool ACPP_Piece::MoveTowards(F2DVectorInt Direction)
{
	if (!MovementOptions.Contains(Direction))
	{
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("WARNING: Piece tried to move in a direction that is not allowed."));
		return false;
	}

	if (!CurrentBoard)
	{
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("!!!WARNING: While moving, this piece has no pointer to the Board!"));
		return false;
	}

	//Verify that the Tile in the CurrentBoard at the BoardPosition location is occupied by this actor
	ACPP_Tile* CurrentTile = CurrentBoard->GetTileAt(BoardPosition);

	if (CurrentTile->OccupyingActor != this)
	{
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("!!!WARNING: While moving, this piece's stored location did not coincide with the board!"));
		return false;
	}

	//Verify that the target Tile exists
	F2DVectorInt TargetPosition = BoardPosition + Direction;
	ACPP_Tile* TargetTile = CurrentBoard->GetTileAt(TargetPosition);

	if (!TargetTile)
	{
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("WARNING: Piece tried to move to a location out of bounds. X %d | Y %d"), TargetPosition.X, TargetPosition.Y));
		return false;
	}

	//Check if target Tile is occupied
	if (TargetTile->bIsOccupied)
	{
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, FString::Printf(TEXT("COMMENT: Piece tried to move to X %d | Y %d, but it is already occupied."), TargetPosition.X, TargetPosition.Y));
		return false;
	}

	//Move this Piece from its current location to the target location
	CurrentTile->OccupyingActor = nullptr;

	TargetTile->OccupyingActor = this;
	BoardPosition = TargetPosition;

	return true;
}

void ACPP_Piece::DestroyPiece()
{
	APlayerPawn* Player = Cast<APlayerPawn>(GetOwner());
	if (Player != nullptr)
	{
		Player->PlayerComponent->RemoveTotalPieces(this);
		Destroy();
	}


}

void ACPP_Piece::Onclicked()
{
	
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("What do you want"));
		
		APlayerPawn* Player = Cast<APlayerPawn>(GetOwner());
		if (Player != nullptr)
		{
			//Player->PlayerComponent->ActionCost(2);
		}
		
		//Move option appears

		//Attack option appears
	

}

void ACPP_Piece::GetTile(ACPP_Tile* Tile)
{

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("Bjorn"));


}

void ACPP_Piece::NotHighlightPiece_Implementation()
{


}

void ACPP_Piece::HighlightPiece_Implementation()
{


}
