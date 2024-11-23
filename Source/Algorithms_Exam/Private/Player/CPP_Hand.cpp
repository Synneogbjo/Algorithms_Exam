// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/CPP_Hand.h"

#include "CPP_Card.h"
#include "CPP_Stack.h"
#include "F2DVectorInt.h"
#include "CPP_Piece.h"

void UCPP_Hand::DrawCard(UCPP_Stack* Stack)
{
	if (!Stack) return;

	if (Cards.Num() >= MaxCards) return;

	Cards.Add(Stack->Pop_Implementation());
}

ACPP_Card* UCPP_Hand::UseCard(int Index, F2DVectorInt PieceLocation)
{
	if (Index < 0 || Index >= Cards.Num()) return nullptr;

	ACPP_Card* TargetCard = Cards[Index];

	Cards[Index] = nullptr;

	for (auto Pile : DrawPiles)
	{
		if (Pile->Role.ClassIndex == TargetCard->CardRole.ClassIndex)
		{
			DrawCard(Pile);

			if (!Pile->DiscardPile) Pile->CreateDiscardPile();

			TargetCard->SpawnEffects(PieceLocation);

			Pile->DiscardPile->AddCardsFromDrawPile(TargetCard);

			break;
		}
	}

	return TargetCard;
}
