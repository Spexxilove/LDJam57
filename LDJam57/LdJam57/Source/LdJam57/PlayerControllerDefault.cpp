// Fill out your copyright notice in the Description page of Project Settings.
#include "PlayerControllerDefault.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"


void APlayerControllerDefault::BeginPlay()
{
	Super::BeginPlay();
	
	//Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
}

void APlayerControllerDefault::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		// Setup mouse input events
		EnhancedInputComponent->BindAction(SetMoveAction, ETriggerEvent::Triggered, this, &APlayerControllerDefault::OnMoveTriggered);
		EnhancedInputComponent->BindAction(SetRotateAction, ETriggerEvent::Triggered, this, &APlayerControllerDefault::OnRotateTriggered);
	}
}


void APlayerControllerDefault::OnMoveTriggered(const FInputActionValue& InputActionValue)
{
	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn != nullptr)
	{
		FVector Direction = InputActionValue.Get<FVector>().X * FVector::ZAxisVector;;
		
		if (ControlledPawn->GetActorLocation().Z>=0)
		{
			if (InputActionValue.Get<FVector>().X>0)
			{
				return;
			}
		}
		else if (ControlledPawn->GetActorLocation().Z<= - maxDepth)
		{
			if (InputActionValue.Get<FVector>().X<0)
			{
				return;
			}
		}
		ControlledPawn->AddMovementInput(Direction);
	}
}

void APlayerControllerDefault::OnRotateTriggered(const FInputActionValue& InputActionValue)
{
	
	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn != nullptr)
	{
		FVector Rotation = InputActionValue.Get<FVector>();
		ControlledPawn->AddControllerPitchInput(Rotation.Y);
		ControlledPawn->AddControllerYawInput(Rotation.Z);
	}
}

void APlayerControllerDefault::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(IsLocalPlayerController())
	{
		// We look for the location in the world where the player has pressed the input
		FHitResult Hit;
		bool bHitSuccessful = false;
		bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);

		// If we hit a surface, cache the location
		if (bHitSuccessful)
		{
			CachedDestination = Hit.Location;
		}
	
		// Move towards mouse pointer or touch
		/* APawn* ControlledPawn = GetPawn();
		if (ControlledPawn != nullptr)
		{
			FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation());
		
			WorldDirection = WorldDirection.GetSafeNormal();
			WorldDirection.Z = 0;
		
			DrawDebugLine(GetWorld(),ControlledPawn->GetActorLocation(), ControlledPawn->GetActorLocation()+WorldDirection*1000,FColor::Red);
			SetControlRotation(FMath::RInterpTo(ControlledPawn->GetActorRotation(), WorldDirection.Rotation(), GetWorld()->GetDeltaSeconds(), 10));
		}*/
	}
}