// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PieceSpawner.h"

#include "CPP_Board.h"
#include "Kismet/GameplayStatics.h"
#include "Player/PlayerComponent.h"

// Sets default values
APieceSpawner::APieceSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APieceSpawner::BeginPlay()
{
	Super::BeginPlay();

	Board = Cast<ACPP_Board>(UGameplayStatics::GetActorOfClass(GetWorld(), ACPP_Board::StaticClass()));

	FTimerHandle TimerHandle;

	// In your BeginPlay implementation

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &APieceSpawner::SpawnPieces, 0.1f, false);

}

// Called every frame
void APieceSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APieceSpawner::SpawnPieces()
{
	if (!Board) return;

	// a loop that will spawn one piece in one location 
	for (int32 i = 0; i<SpawnPoints.Num(); i++)
	{
		ACPP_Tile* SpawnTile = Board->GetTileAt(SpawnPoints[i]);

		if (!SpawnTile) continue;

		if (SpawnTile->bIsOccupied) continue;

		FVector SpawnPoint = SpawnTile->GetActorLocation() + FVector(0.f,0.f, 100.f);

		TSubclassOf<ACPP_Piece> Piece = Pieces[i];

		if (IsValid(Piece))
		{
				ACPP_Piece* SpawnedPiece = GetWorld()->SpawnActor<ACPP_Piece>(Piece, SpawnPoint, FRotator::ZeroRotator);
				
				AssignPlayer(SpawnedPiece);

				SpawnTile->bIsOccupied = true;
				SpawnTile->OccupyingActor = SpawnedPiece;

		}
	}

}

void APieceSpawner::AssignPlayer(ACPP_Piece* Piece)
{
	ACPP_Piece* SpawnedPiece = Piece;

	if (Player != nullptr)
	{
		
		APlayerPawn* CurrentPlayer = Cast<APlayerPawn>(UGameplayStatics::GetActorOfClass(GetWorld(), Player));

		UPlayerComponent* PlayerComponent = CurrentPlayer->FindComponentByClass<UPlayerComponent>();

		if (IsValid(SpawnedPiece))
		{
			//assigns the piece spawned to an array in the player component corresponding to the player
			//that's assign in the blueprint
			PlayerComponent->FillArray(SpawnedPiece);
			SpawnedPiece->SetOwner(CurrentPlayer);
		}
		

	}
	

}

