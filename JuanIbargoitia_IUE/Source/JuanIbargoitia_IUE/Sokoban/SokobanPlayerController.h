#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "SokobanTypes.h"
#include "SokobanPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
class AJuanIbargoitia_IUESokobanPawn;

UCLASS()
class AJuanIbargoitia_IUESokobanPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AJuanIbargoitia_IUESokobanPlayerController();

protected:
	virtual void SetupInputComponent() override;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> MappingContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> RestartAction;

	void OnMoveStarted(const FInputActionValue& Value);
	void OnRestartStarted(const FInputActionValue& Value);

	ESokobanDir AxisToDir(const FVector2D& Axis) const;
};
