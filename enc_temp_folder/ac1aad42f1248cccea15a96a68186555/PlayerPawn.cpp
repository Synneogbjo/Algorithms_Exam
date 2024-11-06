// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerPawn.h"
#include "CPP_Piece.h"
#include "CPP_Tile.h"
#include "EnhancedInputSubsystems.h"
#include "GameplayTagContainer.h"
#include "InputMappingContext.h"
#include "Kismet/GameplayStatics.h"
#include "Player/PlayerComponent.h"

APlayerPawn::APlayerPawn()
{

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(RootComponent);
	// this allow the camera to rotate
	Camera->bUsePawnControlRotation = true;

	PlayerComponent = CreateDefaultSubobject<UPlayerComponent>(TEXT("Player Component"));



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
	FHitResult HitResult;
	FCollisionQueryParams CollisionParams;

	CollisionParams.AddIgnoredActor(this);

	if (UGameplayStatics::GetPlayerController(GetWorld(),0)->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, HitResult))
	{
		if (EDefault == Default)
		{
			if (IsValid(HitResult.GetActor()))
			{

				// check if the player clicked on a piece.
				if (CheckActor(HitResult.GetActor()))
				{
					GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("Fuckkkkky"));
					ACPP_Piece* Piece = Cast<ACPP_Piece>(HitResult.GetActor());
					// access the piece that the player clicked
					Piece->Onclicked();
					SavePreviousPiece(Piece);
					GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::Printf(TEXT("%s"), *Piece->GetOwner()->GetName()));
				}
			}

		}


		if (EDefault == Clicked)
		{
			if (SavedPiece != nullptr)
			{
				//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("give it to me"));
				ACPP_Tile* TileClicked = Cast<ACPP_Tile>(HitResult.GetActor());
				if (IsValid(TileClicked))
				{

					SavedPiece->GetTile(TileClicked);

				}
				

			}

			if (HitResult.GetActor() == SavedPiece)
			{
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("Going to buy milk"));
				Deselect();
			}
			


		}
		
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::Printf(TEXT("%s"), *Piece->GetOwner()->GetName()));
		//EDefault = Clicked;

	}

}

bool APlayerPawn::CheckActor(AActor* Actor)
{
	
	if (Actor !=nullptr)
	{
		ACPP_Piece* Piece = Cast<ACPP_Piece>(Actor);
		
		if (Piece != nullptr)
		{
			
			if (PlayerComponent->PieceBelongToPlayer(Piece))
			{
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("fucking"));

				return true;
				

			}
			

		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("i dont exist"));
		}
	}

	return false;
}

void APlayerPawn::RightMouseButtonIsclicked()
{

	bRightMouseButton = true;
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("ay"));

}

void APlayerPawn::RightMouseButtonNotclicked()
{

	bRightMouseButton = false;
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("Noo"));
}

void APlayerPawn::SavePreviousPiece(ACPP_Piece* ClickedPiece)
{

	SavedPiece = ClickedPiece;
	/*if (SavedPiece == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("you aint' getting this"));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("give it to me"));
	}*/
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::Printf(TEXT("%s"), SavedPiece->GetName()));

}

void APlayerPawn::Deselect()
{

	EDefault = Default;
	SavedPiece = nullptr;

}


