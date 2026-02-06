#include "SokobanGameMode.h"

#include "SokobanGameState.h"
#include "SokobanPawn.h"
#include "SokobanPlayerController.h"

AJuanIbargoitia_IUESokobanGameMode::AJuanIbargoitia_IUESokobanGameMode()
{
	PlayerControllerClass = AJuanIbargoitia_IUESokobanPlayerController::StaticClass();
	DefaultPawnClass = AJuanIbargoitia_IUESokobanPawn::StaticClass();
	GameStateClass = AJuanIbargoitia_IUESokobanGameState::StaticClass();
}
