// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/BoardersGameMode.h"
#include "Player/PlayerPawn.h"
#include "Kismet/GameplayStatics.h"
#include "Player/PlayerComponent.h"

ABoardersGameMode::ABoardersGameMode()
{

	Player1Class = APlayerPawn::StaticClass();
	Player2Class = APlayerPawn::StaticClass();

	CurrentPlayer = nullptr;
	Player1 = nullptr;
	Player2 = nullptr;

}

void ABoardersGameMode::BeginPlay()
{
	Super::BeginPlay();
	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	SpawnPlayers();
	

	CurrentPlayer = PlayerArray[0];
	if (PlayerController != nullptr)
	{
		CurrentPlayer->PossessedBy(PlayerController);
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("Player1"));

	}

}

void ABoardersGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/*FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle ,this, &ABoardersGameMode::SwitchPlayer,4);*/

	//GetWorld()->GetTimerManager().SetTimerForNextTick(this, &ABoardersGameMode::EndGame);

}

void ABoardersGameMode::Enqueue_Implementation(APawn* Actor)
{
	PlayerArray.Emplace(Actor);
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("Player Enqueued"));
}

APawn* ABoardersGameMode::Dequeue_Implementation()
{
	APawn* DequeueActor = nullptr;

	if (!PlayerArray.IsEmpty())
	{
		DequeueActor = PlayerArray[0];
		PlayerArray.RemoveAt(0);

	}

	return DequeueActor;
}

void ABoardersGameMode::SpawnPlayers()
{


	FVector Player1Location = FVector(0, 0, 0);
	FVector Player2Location = FVector(0, 0, 100);
	FRotator Rotation = FRotator::ZeroRotator;
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;


	Player1 = GetWorld()->SpawnActor<APlayerPawn>(Player1Class, Player1Location, Rotation, SpawnParameters);
	Player2 = GetWorld()->SpawnActor<APlayerPawn>(Player2Class, Player2Location, Rotation, SpawnParameters);

	Enqueue_Implementation(Player1);

	Enqueue_Implementation(Player2);

}

void ABoardersGameMode::EndTurn_Implementation()
{

	if (PlayerArray.Num() == 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Empty"));

		return;
	}


	if (IsValid(CurrentPlayer))
	{
		CurrentPlayer->UnPossessed();
	}


	// calls dequeue first and get the pawn return, then call enqueue
	APawn* PlayerDequeued = Dequeue_Implementation();

	if (PlayerDequeued)
	{

		//Enqueue the Player that was removed from the que back into it
		Enqueue_Implementation(PlayerDequeued);

	}




	if (!PlayerArray.IsEmpty())
	{
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Assigned"));

		CurrentPlayer = PlayerArray[0];

		if (IsValid(CurrentPlayer) && IsValid(PlayerController))
		{
			GetWorld()->GetTimerManager().SetTimerForNextTick(this, &ABoardersGameMode::SwitchPlayer);

		}
	}

}

void ABoardersGameMode::SwitchPlayer()
{

	PlayerController->Possess(CurrentPlayer);
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Change to new player"));

}

void ABoardersGameMode::EndGame_Implementation()
{

	UPlayerComponent* Player1Component = Player1->FindComponentByClass<UPlayerComponent>();
	UPlayerComponent* Player2Component = Player2->FindComponentByClass<UPlayerComponent>();
	if (Player1Component->SpawnedPieces.Num() <= 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("End Game Player 2 wins"));

	}
	if (Player2Component->SpawnedPieces.Num() <= 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("End Game Player 1 wins"));

	}
}

//void ABoardersGameMode::EndGame()
//{
//	UPlayerComponent* Player1Component = Player1->FindComponentByClass<UPlayerComponent>();
//	if (Player1Component->SpawnedPieces.Num()<= 0)
//	{
//		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("End Game Player 2 wins"));
//
//	}
//	if (true)
//	{
//		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("End Game Player 1 wins"));
//
//	}
//
//
//}


