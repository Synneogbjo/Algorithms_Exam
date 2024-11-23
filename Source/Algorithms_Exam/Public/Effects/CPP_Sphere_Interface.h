// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CPP_Sphere_Interface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCPP_Sphere_Interface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ALGORITHMS_EXAM_API ICPP_Sphere_Interface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION()
	virtual void UpdateCount();

	
	//ACPP_EffectSphere* SphereRef;

};
