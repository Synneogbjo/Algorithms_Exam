// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PieceSpawner.h"

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

	// a loop that will spawn one piece in one location 
	for (int32 i = 0; i<SpawnPoints.Num(); i++)
	{
		AActor* SpawnPoint = SpawnPoints[i];
		if (IsValid(SpawnPoint))
		{
			FVector SpawnLocation = SpawnPoint->GetActorLocation();

			TSubclassOf<ACPP_Piece> Piece = Pieces[i];
			if (IsValid(Piece))
			{
					ACPP_Piece* SpawnedPiece = GetWorld()->SpawnActor<ACPP_Piece>(Piece, SpawnLocation, FRotator::ZeroRotator);
					
					AssignPlayer(SpawnedPiece);

			}



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
			PlayerComponent->SpawnedPieces.Emplace(SpawnedPiece);

		}
		

	}
	

}

