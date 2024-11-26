// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_Stack.h"

#include "CPP_DiscardPile.h"
#include "Kismet/KismetArrayLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Algo/RandomShuffle.h"

//#include "Kismet/GameplayStatics.h"



//ACardActor* UStacksCard::Pop_Implementation()
//{
//	ACardActor* ClassRef = nullptr;
//	if (!CardsArray.IsEmpty())
//	{
//		ClassRef = CardsArray.Last();
//		CardsArray.Pop();
//		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Cyan, FString::Printf(TEXT("Poped: %s")));
//	}
//
//	return ClassRef; // ClassRef can be used to add the popped card to the hand? or other card stock
//}

void UCPP_Stack::Push_Implementation(ACPP_Card* Card)
{
	if (!Card) return;
	CardsArray.Emplace(Card); //adds new card object to the end (on top)

	/*GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Cyan, FString::Printf(TEXT("Pushed: %s")));
	FVector SpawnLocation = FVector(990.f, 850.f, 92.f);
	FRotator SpawnRotation = FRotator::ZeroRotator;
	FActorSpawnParameters SpawnParameters;
	ClassRef=GetWorld()->SpawnActor<ACardActor>(ACardActor::StaticClass(), SpawnLocation, SpawnRotation, SpawnParameters);*/
}

ACPP_Card* UCPP_Stack::Pop_Implementation()
{
	ACPP_Card* ClassRef = nullptr;
	if (!CardsArray.IsEmpty())
	{
		ClassRef = CardsArray.Last();
		CardsArray.Pop();
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Cyan, FString::Printf(TEXT("Popped")));
	}
	return ClassRef; // ClassRef can be used to add the popped card to the hand? or other card stock
}

void UCPP_Stack::CreateDiscardPile()
{
	if (!DiscardPile) DiscardPile = NewObject<UCPP_DiscardPile>();
}

void UCPP_Stack::InitializeStack()
{
	if (InitCardsClasses.IsEmpty()) return;

	for (auto Class : InitCardsClasses)
	{
		AActor* InitCardActor = GetWorld()->SpawnActor(Class);

		ACPP_Card* InitCard = Cast<ACPP_Card>(InitCardActor);

		if (InitCard) Push_Implementation(InitCard);
	}

	Algo::RandomShuffle(CardsArray);

	UE_LOG(LogTemp, Log, TEXT("Filled the CardsArray %i"), InitCardsClasses.Num());
}
