// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "QueueInterface.h"
#include "GameFramework/GameModeBase.h"
#include "Player/PlayerPawn.h"
#include "BoardersGameMode.generated.h"

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


	UFUNCTION()
	void SpawnPlayers();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Switch Players")
	void EndTurn();

	UFUNCTION()
	void SwitchPlayer();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void EndGame();

};
