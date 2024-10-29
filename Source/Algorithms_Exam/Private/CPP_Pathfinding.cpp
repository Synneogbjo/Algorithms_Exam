// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_Pathfinding.h"

#include "CPP_AlgorithmPath.h"
#include "CPP_Board.h"

TArray<UCPP_AlgorithmPath*> UCPP_Pathfinding::RunPathfinding(F2DVectorInt StartPosition, TArray<F2DVectorInt> MovementOptions, ACPP_Board* Board, int StepAmount)
{
	TArray<UCPP_AlgorithmPath*> LegalPaths;

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

	int Steps = 1;

	//Pathfinding loop
	while (!PositionQueue.IsEmpty() && Steps <= StepAmount)
	{
		UCPP_AlgorithmPath* CurrentPath = PositionQueue[0];

		PositionQueue.RemoveAt(0, 1, true);

		for (int i = 0; i < MovementOptions.Num(); i++)
		{
			F2DVectorInt TargetPosition = CurrentPath->Position + MovementOptions[i];

			if (!TargetPosition.WithinRange(Board->GetBoardSize())) continue;

			if (Board->GetTileAt(TargetPosition)->bIsOccupied) continue;

			auto NewPath = NewObject<UCPP_AlgorithmPath>();
			NewPath->Position = TargetPosition;
			NewPath->PathCost = Steps;
			NewPath->Parent = CurrentPath;

			PositionQueue.Add(NewPath);
		}

		StepAmount++;
	}

	return LegalPaths;
}
