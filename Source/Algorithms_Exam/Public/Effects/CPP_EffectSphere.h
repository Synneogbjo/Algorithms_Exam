// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Effects/CPP_EffectParent.h"
#include "CPP_Piece.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "CPP_Piece.h"
#include "CPP_EffectSphere.generated.h"

/* Effect Sphere delegate*/
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnDealDamageDelegate,class ACPP_Piece*, PieceInside);  //DECLARE_DELEGATE_OneParam(DelegateName, Param1Type) Param1 should be of type you want to use 

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

	/*Delegates*/

	UPROPERTY()
	FOnDealDamageDelegate SphereDelegate;
	/**/

	UPROPERTY()
	ACPP_Piece* PieceRef;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool fromSweep, const FHitResult& result);

	UPROPERTY()
	bool WasCalled = false;

	UPROPERTY()
	bool IsInside = false;

	UFUNCTION()
	void DealDamage(ACPP_Piece* PieceInside);



};
