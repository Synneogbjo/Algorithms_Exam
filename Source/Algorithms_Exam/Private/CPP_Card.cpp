// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_Card.h"

// Sets default values
ACPP_Card::ACPP_Card()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CardCost = 0;
	//CardRole = ? ;
}

// Called when the game starts or when spawned
void ACPP_Card::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACPP_Card::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

