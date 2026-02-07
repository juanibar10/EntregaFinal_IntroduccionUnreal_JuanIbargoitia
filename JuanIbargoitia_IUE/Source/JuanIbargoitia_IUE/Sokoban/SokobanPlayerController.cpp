#include "SokobanPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "Kismet/GameplayStatics.h"

#include "SokobanPawn.h"
#include "JuanIbargoitia_IUE.h"

AJuanIbargoitia_IUESokobanPlayerController::AJuanIbargoitia_IUESokobanPlayerController()
{
	bShowMouseCursor = false;
	DefaultMouseCursor = EMouseCursor::Default;
}

void AJuanIbargoitia_IUESokobanPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (!IsLocalPlayerController())
	{
		return;
	}

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		if (MappingContext)
		{
			Subsystem->AddMappingContext(MappingContext, 0);
		}
		else
		{
			UE_LOG(LogJuanIbargoitia_IUE, Warning, TEXT("SokobanPlayerController: MappingContext no asignado (asígnalo en el BP del controller o en defaults)."));
		}
	}

	if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(InputComponent))
	{
		if (MoveAction)
		{
			EIC->BindAction(MoveAction, ETriggerEvent::Started, this, &AJuanIbargoitia_IUESokobanPlayerController::OnMoveStarted);
		}
		if (RestartAction)
		{
			EIC->BindAction(RestartAction, ETriggerEvent::Started, this, &AJuanIbargoitia_IUESokobanPlayerController::OnRestartStarted);
		}
	}
	else
	{
		UE_LOG(LogJuanIbargoitia_IUE, Error, TEXT("SokobanPlayerController: No se encontró EnhancedInputComponent."));
	}
}

ESokobanDir AJuanIbargoitia_IUESokobanPlayerController::AxisToDir(const FVector2D& Axis)
{
	const float AbsX = FMath::Abs(Axis.X);
	const float AbsY = FMath::Abs(Axis.Y);
	if (AbsX >= AbsY)
	{
		return (Axis.X >= 0.f) ? ESokobanDir::Right : ESokobanDir::Left;
	}
	return (Axis.Y >= 0.f) ? ESokobanDir::Up : ESokobanDir::Down;
}

void AJuanIbargoitia_IUESokobanPlayerController::OnMoveStarted(const FInputActionValue& Value)
{
	const FVector2D Axis = Value.Get<FVector2D>();
	if (Axis.IsNearlyZero())
	{
		return;
	}

	AJuanIbargoitia_IUESokobanPawn* P = Cast<AJuanIbargoitia_IUESokobanPawn>(GetPawn());
	if (!P || P->IsMoving())
	{
		return;
	}

	const ESokobanDir Dir = AxisToDir(Axis);
	P->RequestStep(Dir);
}

void AJuanIbargoitia_IUESokobanPlayerController::OnRestartStarted(const FInputActionValue& Value)
{
	UWorld* World = GetWorld();
	if (!World) return;

	const FName CurrentLevelName(*UGameplayStatics::GetCurrentLevelName(World, true));
	UGameplayStatics::OpenLevel(this, CurrentLevelName);
}
