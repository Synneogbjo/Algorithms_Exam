// Fill out your copyright notice in the Description page of Project Settings.


#include "Effects/CPP_EffectSphere.h"
//#include "GameMode/BoardersGameMode.h"


ACPP_EffectSphere::ACPP_EffectSphere()
{
	EffectType = DAMAGE;
	TriggerSphere = CreateDefaultSubobject<USphereComponent>(TEXT("SphereTrigger"));
	TriggerSphere->SetupAttachment(GetRootComponent());
	TriggerSphere->InitSphereRadius(3.0);
	TriggerSphere->OnComponentBeginOverlap.AddDynamic(this, &ACPP_EffectSphere::OnBeginOverlap);



}

void ACPP_EffectSphere::BeginPlay()
{
	Super::BeginPlay();

	//GetWorldTimerManager().SetTimer(DestroySphere, this, &ACPP_EffectSphere::DestroyIfNoCollision, 0.5f);


	SphereDelegate.BindDynamic(this,&ACPP_EffectSphere::DealDamage);

}




void ACPP_EffectSphere::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool fromSweep, const FHitResult& result)
{

	if (OtherActor->IsA(ACPP_Piece::StaticClass()))
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, FString::Printf(TEXT("Hit")));
			PieceRef = Cast<ACPP_Piece>(OtherActor);
			PieceRef->Damage(1);
			IsInside = true;
			WasCalled = true;
		}
	}
	
	else
	{
		
	}
}

void ACPP_EffectSphere::DealDamage(ACPP_Piece* PieceInside)
{
	if (IsInside)
	{
		if (IsValid(PieceRef))
		{
			PieceRef->Damage(1);
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("ouch"));
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("fuck"));
		}
	}


	
}





