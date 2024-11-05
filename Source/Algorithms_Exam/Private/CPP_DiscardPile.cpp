// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_DiscardPile.h"

void UCPP_DiscardPile::AddCardsFromDrawPile(ACPP_Card* Card, TArray<ACPP_Card*>& Array)
{
	if (!Card) return;
	DiscardPileArray.Add(Card);
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Cyan, FString::Printf(TEXT("Orignal first card: %d"), Card->CardRole.ClassIndex));

	//shuffle
	for (int32 i = DiscardPileArray.Num() - 1; i > 0; i--)
	{
		int32 SwapingIndex = FMath::RandRange(0, i);
		DiscardPileArray.Swap(i, SwapingIndex);
	}
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Cyan, FString::Printf(TEXT("Shuffled")));
}

ACPP_Card* UCPP_DiscardPile::EmptyDiscardPile()
{
	//empty discard pile
	ACPP_Card* CardRef = nullptr;
	if (!DiscardPileArray.IsEmpty())
	{ 
		CardRef = DiscardPileArray.Last();
		DiscardPileArray.Pop();
	}
	return CardRef;
}

void UCPP_DiscardPile::AddCardsToShuffledPile(ACPP_Card* CardRef)
{
	for (auto i : DiscardPileArray) {
		EmptyDiscardPile();
		//save shuffled cards inside shuffled array, ready to be sent to draw pile
		if (!CardRef) return;
		else {
			ShuffledArray.Add(CardRef);
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Cyan, FString::Printf(TEXT("Popped")));
		}
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Cyan, FString::Printf(TEXT("Orignal first card: %d"), CardRef->CardRole.ClassIndex));
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Cyan, FString::Printf(TEXT("number of cards in shuffled: %d"), ShuffledArray.Num()));
	}
}


