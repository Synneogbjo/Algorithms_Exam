// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "QueueInterface.h"
#include "GameFramework/GameModeBase.h"
#include "Player/PlayerPawn.h"
#include "Components/ActorComponent.h" //UI
#include "EndGameWidget.h"
#include "Effects/CPP_EffectParent.h"
#include "Effects/CPP_EffectSphere.h"
#include "BoardersGameMode.generated.h"

class UEndGameWidget;



/**
 * 
 */
UCLASS()
class ALGORITHMS_EXAM_API ABoardersGameMode : public AGameModeBase, public IQueueInterface, public ICPP_Sphere_Interface
{
	GENERATED_BODY()

	int TurnCount=0;

	

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

	UFUNCTION()
	void SpawnPlayers();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Switch Players")
	void EndTurn();

	UFUNCTION()
	void SwitchPlayer();

	UFUNCTION()
	void ResetPlayer(APawn* Player);

	//PLayer widgets switch

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent, Category="PlayerWidgetSwitch")
	void Player1WidgetSwitch();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PlayerWidgetSwitch")
	void Player2WidgetSwitch();

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

	/*Effect Sphere*/

	UPROPERTY(EditAnywhere, Category = "Effects")
	TSubclassOf<ACPP_EffectSphere> EffectSphereClass;

	UPROPERTY(EditAnywhere,BlueprintReadWrite ,Category = "Effects")
	ACPP_EffectSphere* EffectSphereRef;

	UPROPERTY()
	TArray<AActor*> FoundActors;

	
};
