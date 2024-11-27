// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_DiscardPile.h"

void UCPP_DiscardPile::AddCardsFromDrawPile(ACPP_Card* Card)
{
	if (!Card) return;
	DiscardPileArray.Add(Card);
	
	//shuffle
	for (int32 i = DiscardPileArray.Num() - 1; i > 0; i--)
	{
		int32 SwapingIndex = FMath::RandRange(0, i);
		DiscardPileArray.Swap(i, SwapingIndex);
	}
}

ACPP_Card* UCPP_DiscardPile::EmptyDiscardPile()
{
	
	ACPP_Card* CardRef = nullptr;
	if (!DiscardPileArray.IsEmpty())
	{ 
		CardRef = DiscardPileArray.Last();
		DiscardPileArray.Pop();
	}
	return CardRef;
}

void UCPP_DiscardPile::AddCardsToShuffledPile()
{
	ACPP_Card* CardRef = nullptr;

	int DiscardPileSize = DiscardPileArray.Num();

	for (int i = 0; i < DiscardPileSize; i++) {
		CardRef = EmptyDiscardPile();
		//save shuffled cards inside shuffled array, ready to be sent to draw pile
		if (!CardRef) return;
		else {
			ShuffledArray.Add(CardRef);
			
		}
	}
	
}


