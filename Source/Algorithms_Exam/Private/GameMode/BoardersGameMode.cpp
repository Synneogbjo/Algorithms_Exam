// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/BoardersGameMode.h"

#include "EndGameWidget.h"
#include "Player/PlayerPawn.h"
#include "UIComponent.h"
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
	


	//for testing end game widget
	UPlayerComponent* Player2Component = Player2->FindComponentByClass<UPlayerComponent>();
	Player2Component->SpawnedPieces.SetNum(0);
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("constructor is called"));
	EndGame_Implementation();
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

//FString ABoardersGameMode::SendPlayerName(FString Name)
//{
//	EndGameWidgetRef->DisplayWinner(Name);
//	return Name;
//}

void ABoardersGameMode::SpawnPlayers()
{
	const FRotator Rotation = FRotator::ZeroRotator;
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;


	Player1 = GetWorld()->SpawnActor<APlayerPawn>(Player1Class, PLayer1SpawnLocation(), Rotation, SpawnParameters);
	Player2 = GetWorld()->SpawnActor<APlayerPawn>(Player2Class, PLayer2SpawnLocation(), Rotation, SpawnParameters);

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
		ResetPlayer(CurrentPlayer);
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

void ABoardersGameMode::ResetPlayer(APawn* Player)
{
	if (Player == Player1)
	{

		//logic to place player back to the starting position
		//reset points so player can use his points again

		Player->SetActorLocation(PLayer1SpawnLocation());

		UPlayerComponent* PlayerComponent = Player->FindComponentByClass<UPlayerComponent>();
		if (IsValid(PlayerComponent))
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("Update Points"));
			PlayerComponent->RefillPoints();
		}
			


	}
	if (Player == Player2)
	{
		

		Player->SetActorLocation(PLayer2SpawnLocation());

		UPlayerComponent* PlayerComponent = Player->FindComponentByClass<UPlayerComponent>();
		if (IsValid(PlayerComponent))
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("Update Points"));
			PlayerComponent->RefillPoints();
			
		}

	}


}

FVector ABoardersGameMode::PLayer1SpawnLocation()
{
	const AActor* SpawnPoint1 = UGameplayStatics::GetActorOfClass(GetWorld(), Player1SpawnPoint);

	const FVector Player1Location = SpawnPoint1->GetActorLocation();
	return Player1Location;
}

FVector ABoardersGameMode::PLayer2SpawnLocation()
{
	const AActor* SpawnPoint2 = UGameplayStatics::GetActorOfClass(GetWorld(), Player2SpawnPoint);
	const FVector Player2Location = SpawnPoint2->GetActorLocation();
	return Player2Location;

}

void ABoardersGameMode::EndGame_Implementation()
{

	UPlayerComponent* Player1Component = Player1->FindComponentByClass<UPlayerComponent>();
	UPlayerComponent* Player2Component = Player2->FindComponentByClass<UPlayerComponent>();
	//if (Player1Component->SpawnedPieces.Num() <= 0)
	//{
	//	//UUIComponent(); ////call this constructor to create widget, add it to viewport
	//	//DisplayWinner(Player1);

	//	// it would be best to create the end game widget and add it to the screen
	//	//SendPlayerName(Player1Component->PlayerName);
	//	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("End Game Player 2 wins"));

	//}
	if (Player2Component->SpawnedPieces.Num() <= 0)
	{

		//UUIComponent(); ////call this constructor to create widget, add it to viewport
		//DisplayWinner(Player1);


		//SendPlayerName(Player2Component->PlayerName);
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


