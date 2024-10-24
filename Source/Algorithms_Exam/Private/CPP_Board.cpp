// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_Board.h"

#include "Engine/Engine.h"

// Sets default values
ACPP_Board::ACPP_Board()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(GetRootComponent());

	TeamAffiliationRowCount = 0;
	InitBoardDepth = 0.1f;
	InitBoardPadding = 0;
	InitBoardMargin = 0;
}

// Called when the game starts or when spawned
void ACPP_Board::BeginPlay()
{
	Super::BeginPlay();

	SetBoardSize(InitBoardSize);

	SetBoardTeamAffiliation(TeamAffiliationRowCount);

	DrawBoard(GetActorLocation(), TileSize, InitBoardDepth, InitBoardPadding, InitBoardMargin);
	
}

// Called every frame
void ACPP_Board::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

/// Empties the board, and fills it with new tiles.
/// @param Size The width of the board
/// @return Whether the function managed to run correctly
bool ACPP_Board::SetBoardSize(const F2DVectorInt Size)
{
	bool bNoErrors = true;
	
	TileArray2D.Empty();

	for (int w = 0; w < Size.X; w++)
	{
		TileArray2D.Emplace(NewObject<UFTileArray>());

		for (int h = 0; h < Size.Y; h++)
		{
			auto NewTile = GetWorld()->SpawnActor<ACPP_Tile>(TileActor, FVector(0, 0, 0), FRotator(0, 0, 0));
			TileArray2D[w]->TileArray.Emplace(NewTile);
			if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::White, TEXT("Creating Board"));
		}
	}

	return bNoErrors;
}

/// Tries to change the team affiliation of tiles in the board.
/// @param TeamRowCount How many rows will be affiliated with each team
/// @return Whether the function managed to run correctly or not
bool ACPP_Board::SetBoardTeamAffiliation(const int TeamRowCount)
{
	if (TileArray2D.Num() < (2 * TeamRowCount))
	{
		return false;
	}

	for (int r = 0; r < TeamRowCount; r++)
	{
		//Sets Team Affiliation for Team 1
		for (int t = 0; t < TileArray2D[r]->TileArray.Num(); t++)
		{
			TileArray2D[r]->TileArray[t]->TeamAffiliation = 1;
		}

		//Sets Team Affiliation for Team 2
		for (int t = 0; t < TileArray2D[TileArray2D.Num() - 1 - r]->TileArray.Num(); t++)
		{
			TileArray2D[TileArray2D.Num() - 1 - r]->TileArray[t]->TeamAffiliation = 2;
		}
	}

	return true;
}

/// Tries to get the tile at desired location within the board
/// @param X Index of first array
/// @param Y Index of second array
/// @return Pointer to the desired tile
ACPP_Tile* ACPP_Board::GetTileAt(const int X, const int Y)
{
	//Makes sure the targeted tile is inside of range, and exists

	if (TileArray2D.IsEmpty()) return nullptr;

	if (X >= TileArray2D.Num()) return nullptr;

	const TArray<ACPP_Tile*> T = TileArray2D[X]->TileArray;

	if (T.IsEmpty()) return nullptr;

	if (Y >= T.Num()) return nullptr;

	//Returns pointer to desired tile
	return T[Y];
}

F2DVectorInt ACPP_Board::GetBoardSize()
{
	F2DVectorInt BoardSize(-1,-1);

	BoardSize.X = TileArray2D.Num();
	BoardSize.Y = TileArray2D[0]->TileArray.Num();

	return BoardSize;
}

void ACPP_Board::DrawBoard(const FVector BoardLocation, const FVector TilesSize, const float BackgroundDepth, const float Padding, const float Margin)
{
	FVector TargetLocation = BoardLocation;

	TargetLocation.X += Margin;
	TargetLocation.Y += Margin;

	for (int x = 0; x < TileArray2D.Num(); x++)
	{
		TArray<ACPP_Tile*> TileArray = TileArray2D[x]->TileArray;

		TargetLocation.Y = BoardLocation.Y;

		for (int y = 0; y < TileArray.Num(); y++)
		{
			TileArray[y]->DrawTile(TargetLocation, TilesSize);

			TargetLocation.Y += TilesSize.Y + Padding;
		}

		TargetLocation.X += TilesSize.X + Padding;
	}

	const FVector MeshScale = FVector((GetBoardSize().X * (TileSize.X + Padding)) + (2 * Margin), (GetBoardSize().Y * (TileSize.Y + Padding)) + (2 * Margin), BackgroundDepth)/100.f;

	Mesh->SetWorldLocation(((BoardLocation + TargetLocation - FVector(0.f, Margin, InitBoardDepth * 2)) / 2));
	Mesh->SetWorldScale3D(MeshScale);
}
