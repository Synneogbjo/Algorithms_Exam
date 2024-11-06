// Fill out your copyright notice in the Description page of Project Settings.


#include "Effects/CPP_EffectDamage.h"

#include "CPP_Piece.h"
#include "Components/BoxComponent.h"

ACPP_EffectDamage::ACPP_EffectDamage()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetupAttachment(GetRootComponent());
	TriggerBox->SetBoxExtent(FVector(1, 1, 1));
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ACPP_EffectDamage::OnBeginOverlap);
}

// Called when the game starts or when spawned
void ACPP_EffectDamage::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(DestroyTimer, this, &ACPP_EffectDamage::DestroyIfNoCollision, 0.5f);
}

// Called every frame
void ACPP_EffectDamage::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACPP_EffectDamage::OnBeginOverlap(UPrimitiveComponent*OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool fromSweep, const FHitResult& result)
{
	if (OtherActor->IsA(ACPP_Piece::StaticClass()))
	{
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, FString::Printf(TEXT("Hit actor")).Append(OtherActor->GetName()));

		Cast<ACPP_Piece>(OtherActor)->Damage(1);

		Destroy();
	}
	else
	{
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Hit unknown actor! ")).Append(OtherActor->GetName()));
	}
}

void ACPP_EffectDamage::DestroyIfNoCollision()
{
	UE_LOG(LogTemp, Log, TEXT("Effect Damage Did not hit anything!"));
	Destroy();
}