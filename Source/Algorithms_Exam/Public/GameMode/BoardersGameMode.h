// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "QueueInterface.h"
#include "GameFramework/GameModeBase.h"
#include "Player/PlayerPawn.h"
#include "Components/ActorComponent.h" //UI
#include "EndGameWidget.h"
#include "BoardersGameMode.generated.h"

class UEndGameWidget;
/**
 * 
 */
UCLASS()
class ALGORITHMS_EXAM_API ABoardersGameMode : public AGameModeBase, public IQueueInterface
{
	GENERATED_BODY()

public:
	ABoardersGameMode();


protected:

	virtual void BeginPlay() override;


public:

	virtual void Tick(float DeltaTime) override;


	//From QueueInterface
	virtual void Enqueue_Implementation(APawn* Actor) override;

	virtual APawn* Dequeue_Implementation() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QueueArray")
	TArray<APawn*> PlayerArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerClass")
	TSubclassOf<APlayerPawn> Player1Class;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerClass")
	TSubclassOf<APlayerPawn> Player2Class;


	UPROPERTY()
	APawn* CurrentPlayer;


	UPROPERTY()
	APlayerPawn* Player1;

	UPROPERTY()
	APlayerPawn* Player2;

	UPROPERTY()
	APlayerController* PlayerController = nullptr;


	// spawn points for players
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="SpawnPoint")
	TSubclassOf<AActor> Player1SpawnPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnPoint")
	TSubclassOf<AActor> Player2SpawnPoint;

	/*UFUNCTION(BlueprintCallable)
	FString SendPlayerName(FString Name);*/

	UFUNCTION()
	void SpawnPlayers();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Switch Players")
	void EndTurn();

	UFUNCTION()
	void SwitchPlayer();

	UFUNCTION()
	void ResetPlayer(APawn* Player);

	UFUNCTION()
	FVector PLayer1SpawnLocation();

	UFUNCTION()
	FVector PLayer2SpawnLocation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void EndGame();


	/*End Game UI*/
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UEndGameWidget> UEndGameWidgetClass;

	UUserWidget* CreateUIWidget(TSubclassOf<UEndGameWidget> WidgetClass);

	UPROPERTY()
	UEndGameWidget* UIInstance;

	/*UFUNCTION(BlueprintCallable, Category = "UI")
	UEndGameWidget* GetUIWidget() { return UIInstance; }*/


};
