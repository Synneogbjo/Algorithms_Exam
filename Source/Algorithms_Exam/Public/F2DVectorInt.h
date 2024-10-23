// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "F2DVectorInt.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class ALGORITHMS_EXAM_API UF2DVectorInt : public UObject
{
	GENERATED_BODY()

	UF2DVectorInt();
	UF2DVectorInt(const int SetX, const int SetY);

	int X;
	int Y;
};
