// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_Piece.h"

#include "Components/BoxComponent.h"

// Sets default values
ACPP_Piece::ACPP_Piece()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	SetRootComponent(TriggerBox);

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComponent->SetupAttachment(GetRootComponent());

	/*
	 * Variable Initialization
	 */

	MaxHealth = Health = 4;
	BoardPosition = F2DVectorInt(-1, -1);

}

// Called when the game starts or when spawned
void ACPP_Piece::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACPP_Piece::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

/// <summary>
/// Changes the Health of this Piece by the Value inserted. Positive Values will do damage, Negative Values will heal.
/// </summary>
/// <param name="Value"> Damage to deal </param>
/// <returns> Current Health after dealing Damage </returns>
int ACPP_Piece::Damage(int Value)
{
	if ((Health - Value) >= MaxHealth)
	{
		Health = MaxHealth;
	}
	else
	{
		Health -= Value;
	}

	return Health;
}

