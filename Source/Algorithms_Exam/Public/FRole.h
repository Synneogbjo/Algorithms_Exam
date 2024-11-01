// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FTeam.h"

#include "FRole.generated.h"

class UPaperSprite;

/**
 * 
 */
USTRUCT(Blueprintable)
struct ALGORITHMS_EXAM_API FRole
{
public:

	GENERATED_BODY()


	FRole();
	FRole(FTeam SetTeam, FString SetName);
	FRole(FTeam SetTeam, FString SetName, UPaperSprite* SetSprite);
	~FRole();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Role")
	FTeam RoleTeam;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Role")
	FString RoleName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Role")
	UPaperSprite* RoleSprite;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Role")
	int32 ClassIndex=0;
};
