// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Effects/CPP_EffectParent.h"
#include "CPP_Piece.h"
#include "Components/SphereComponent.h"
#include "BoardersGameMode.generated.h"
#include "Kismet/GameplayStatics.h"
#include "CPP_EffectSphere.generated.h"

/**
 * 
 */
UCLASS()
class ALGORITHMS_EXAM_API ACPP_EffectSphere : public ACPP_EffectParent
{
	GENERATED_BODY()

	FTimerHandle DestroySphere;
public:

	ACPP_EffectSphere();

	void BeginPlay();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect")
	USphereComponent* TriggerSphere;




	//ABoardersGameMode* CurrentGameMode = Cast<CurrentGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	/*UPROPERTY()
	ABoardersGameMode* CurrentGameMode = reinterpret_cast<ABoardersGameMode*>(GetWorld()->GetAuthGameMode());*/

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool fromSweep, const FHitResult& result);

	UFUNCTION()
	void DestroyIfNoCollision();


};
