// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "F2DVectorInt.generated.h"

/**
 * 
 */
USTRUCT(Blueprintable)
struct ALGORITHMS_EXAM_API F2DVectorInt
{
	GENERATED_BODY()

	F2DVectorInt();
	F2DVectorInt(const int SetX, const int SetY);

	~F2DVectorInt();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "2D Vector Int")
	int X;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "2D Vector Int")
	int Y;
};
