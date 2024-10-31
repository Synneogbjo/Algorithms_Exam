// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_Pathfinding.h"

#include "CPP_AlgorithmPath.h"
#include "CPP_Board.h"
#include "Algo/Find.h"


ACPP_Pathfinding::ACPP_Pathfinding()
{
	// Set this actor to call Tick() every frame if needed. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

TArray<UCPP_AlgorithmPath*> ACPP_Pathfinding::RunPathfinding(F2DVectorInt StartPosition, TArray<F2DVectorInt> MovementOptions, ACPP_Board* Board, int StepAmount)
{
	TArray<UCPP_AlgorithmPath*> LegalPaths = {};

	//Failsafe checks
	if (MovementOptions.IsEmpty()) return LegalPaths;

	if (!Board) return LegalPaths;

	if (!StartPosition.WithinRange((Board->GetBoardSize()))) return LegalPaths;


	//Traversal Queue
	TArray<UCPP_AlgorithmPath*> PositionQueue;

	auto StartPath = NewObject<UCPP_AlgorithmPath>();
	StartPath->Position = StartPosition;
	StartPath->PathCost = 0;

	PositionQueue.Add(StartPath);

	int Steps = 0;

	//Pathfinding loop
	while (!PositionQueue.IsEmpty() && Steps <= StepAmount)
	{
		Steps++;

		int PositionQueueCount = PositionQueue.Num();

		for (int a = 0; a < PositionQueueCount; a++) {

			UCPP_AlgorithmPath* CurrentPath = PositionQueue[0];

			LegalPaths.Add(CurrentPath);

			PositionQueue.RemoveAt(0, 1, true);

			for (int i = 0; i < MovementOptions.Num(); i++)
			{
				F2DVectorInt TargetPosition = CurrentPath->Position + MovementOptions[i];

				if (!TargetPosition.WithinRange(Board->GetBoardSize())) continue;

				bool bTargetPositionIsSaved = false;

				//Checks if the current TargetPosition has already been found, then move on to the next TargetPosition
				for (int p = 0; p < LegalPaths.Num(); p++)
				{
					if (TargetPosition == LegalPaths[p]->Position)
					{
						UE_LOG(LogTemp, Warning, TEXT("Target: %d,%d | Saved: %d,%d"), TargetPosition.X, TargetPosition.Y, LegalPaths[p]->Position.X, LegalPaths[p]->Position.Y);

						bTargetPositionIsSaved = true;
						break;
					}
				}

				if (bTargetPositionIsSaved) continue;

				if (!Board->GetTileAt(TargetPosition)) continue;

				if (Board->GetTileAt(TargetPosition)->bIsOccupied) continue;

				auto NewPath = NewObject<UCPP_AlgorithmPath>();
				NewPath->Position = TargetPosition;
				NewPath->PathCost = Steps;
				NewPath->Parent = CurrentPath;

				PositionQueue.Add(NewPath);
			}
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("Legal Path Amount: %d"), LegalPaths.Num());

	return LegalPaths;
}
