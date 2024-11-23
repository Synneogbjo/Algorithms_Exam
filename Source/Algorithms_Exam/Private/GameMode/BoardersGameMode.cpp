// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/BoardersGameMode.h"

#include "EndGameWidget.h"
#include "Player/PlayerPawn.h"
//#include "UIComponent.h"
#include "EndGameWidget.h"
#include "ToolBuilderUtil.h"
#include "Blueprint/UserWidget.h"
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
		SwitchPlayer();
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("Player1"));

	}

	/*FActorSpawnParameters SpawnParam;
	FVector SpawnLocation = {640.0f,-230.0f,30.0f};

	TArray<AActor*> Arrayofstuff;
	TArray<AActor> a = UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACPP_EffectSphere::StaticClass(), Arrayofstuff);
	 EffectSphereRef = a[0];*/
		
	//EndGame_Implementation();

	
	
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
		auto PlayerPawn = Cast<APlayerPawn>(CurrentPlayer);
		if (PlayerPawn)
		{
			auto Piece = PlayerPawn->SavedPiece;

			if (Piece)
			{
				Piece->ClearVisualizePathfinding();
			}

			PlayerPawn->Deselect();
		}

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
	if (CurrentPlayer ==Player1)
	{
		Player1WidgetSwitch();
	}
	else if (CurrentPlayer == Player2)
	{
		Player2WidgetSwitch();
	}
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("%s"), *CurrentPlayer->GetName()));

	/* Effect sphere long term damage*/
	if(EffectSphereRef == nullptr)
	{
		EffectSphereRef = Cast<ACPP_EffectSphere>(UGameplayStatics::GetActorOfClass(GetWorld(),EffectSphereClass));
		
	}
	if (IsValid(EffectSphereRef))
	{
		TurnCount++;
		if (TurnCount == 2) //i want to call deal damage only when its my turn again
		{
			EffectSphereRef->SphereDelegate.ExecuteIfBound(EffectSphereRef->PieceRef); //this calls deal damage function again
		}
	}
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
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("Update Points"));
			PlayerComponent->RefillPoints();

			for (auto Piece : PlayerComponent->SpawnedPieces)
			{
				Piece->CurrentMovementCost = 0;
			}
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

			for (auto Piece : PlayerComponent->SpawnedPieces)
			{
				Piece->CurrentMovementCost = 0;
			}			
		}

	}

}

void ABoardersGameMode::Player1WidgetSwitch_Implementation()
{
}


void ABoardersGameMode::Player2WidgetSwitch_Implementation()
{
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



UUserWidget* ABoardersGameMode::CreateUIWidget(TSubclassOf<UEndGameWidget> WidgetClass)
{
	if (WidgetClass) {
		UIInstance = CreateWidget<UEndGameWidget>(GetWorld(), WidgetClass);
		if (UIInstance) {
			UIInstance->AddToViewport();
		}
	}
	return UIInstance;
}


void ABoardersGameMode::EndGame_Implementation()
{

	UPlayerComponent* Player1Component = Player1->FindComponentByClass<UPlayerComponent>();
	UPlayerComponent* Player2Component = Player2->FindComponentByClass<UPlayerComponent>();
	if (Player1Component->SpawnedPieces.Num() <= 0 || Player1Component->SpawnedPieces.Num() > Player2Component->SpawnedPieces.Num())
	{
		CreateUIWidget(UEndGameWidgetClass);
		if (UEndGameWidgetClass)
		{
			UIInstance->Text->SetText(FText::FromString(TEXT("Player2 wins!")));
		}
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("End Game Player 2 wins"));

	}
	if (Player2Component->SpawnedPieces.Num() <= 0 || Player2Component->SpawnedPieces.Num() > Player1Component->SpawnedPieces.Num())
	{
		CreateUIWidget(UEndGameWidgetClass);
		if(UEndGameWidgetClass)
		{
			UIInstance->Text->SetText(FText::FromString(TEXT("Player1 wins!")));
		}
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("End Game Player 1 wins"));
	}
}



