#include "SokobanPlayerController.h"

ASokobanPlayerController::ASokobanPlayerController()
{
	bShowMouseCursor = false;
	bEnableClickEvents = false;
	bEnableMouseOverEvents = false;
}

void ASokobanPlayerController::BeginPlay()
{
	Super::BeginPlay();
}
