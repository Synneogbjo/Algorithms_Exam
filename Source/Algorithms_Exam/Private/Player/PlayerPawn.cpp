// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerPawn.h"
#include "EnhancedInputSubsystems.h"
#include "GameplayTagContainer.h"
#include "InputMappingContext.h"
#include "Kismet/GameplayStatics.h"

APlayerPawn::APlayerPawn()
{

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(RootComponent);
	// this allow the camera to rotate
	Camera->bUsePawnControlRotation = true;
	TotalPieces = 0;

}

void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();

	if (const APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(Imc, 0);
		}
	}


}

void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

	EnhancedInputComponent->BindAction(Wasd, ETriggerEvent::Triggered, this, &APlayerPawn::PlayerMovement);
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerPawn::CameraLook);
	EnhancedInputComponent->BindAction(ClickLeftAction, ETriggerEvent::Triggered, this, &APlayerPawn::OnClick);

	EnhancedInputComponent->BindAction(ClickRightAction, ETriggerEvent::Ongoing, this, &APlayerPawn::RightMouseButtonIsclicked);
	EnhancedInputComponent->BindAction(ClickRightAction, ETriggerEvent::Completed, this, &APlayerPawn::RightMouseButtonNotclicked);
}

void APlayerPawn::PlayerMovement(const FInputActionValue& Value)
{

	const FVector2D MoveInput = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		const FRotator YawPlayerRotation = FRotator(0, GetControlRotation().Yaw, 0);

		const FVector ForwardBackwards = FRotationMatrix(YawPlayerRotation).GetUnitAxis(EAxis::Y);

		const FVector RightDirection = FRotationMatrix(YawPlayerRotation).GetUnitAxis(EAxis::X);


		AddMovementInput(ForwardBackwards, MoveInput.X);
		AddMovementInput(RightDirection, MoveInput.Y);
	}

}

void APlayerPawn::CameraLook(const FInputActionValue& Value)
{

	const FVector2D LookInput = Value.Get<FVector2D>();

	if (bRightMouseButton)
	{
		AddControllerYawInput(LookInput.X);

		AddControllerPitchInput(LookInput.Y);

	}

}

void APlayerPawn::OnClick()
{

	FVector2D MousePos = FVector2D(0,0);

	UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetMousePosition(MousePos.X, MousePos.Y);


	const FVector StartTrace = FVector(MousePos.X, MousePos.Y, 0);
	FVector EndTrace = StartTrace + Camera->GetComponentRotation().Vector() * 1000;

	FHitResult HitResult;
	FCollisionQueryParams CollisionParams;

	CollisionParams.AddIgnoredActor(this);

	if (UGameplayStatics::GetPlayerController(GetWorld(),0)->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, HitResult))
		//LineTraceSingleByChannel(HitResult, StartTrace, EndTrace, ECC_Visibility, CollisionParams))
	{
		
		AActor* test = HitResult.GetActor();
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::Printf(TEXT("%s"), *test->GetName()));


		//GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
	}




}

void APlayerPawn::RightMouseButtonIsclicked()
{

	bRightMouseButton = true;
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("ay"));

}

void APlayerPawn::RightMouseButtonNotclicked()
{

	bRightMouseButton = false;
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("Noo"));
}
