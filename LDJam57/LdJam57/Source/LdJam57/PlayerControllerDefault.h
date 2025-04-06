// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerControllerDefault.generated.h"

/**
 * 
 */
UCLASS()
class LDJAM57_API APlayerControllerDefault : public APlayerController
{
	GENERATED_BODY()

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* SetMoveAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* SetRotateAction;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int maxDepth = 500;


	
	FVector CachedDestination;

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	void OnMoveTriggered(const struct FInputActionValue& InputActionValue);
	void OnRotateTriggered(const FInputActionValue& InputActionValue);
	virtual void Tick(float DeltaSeconds) override;
};
