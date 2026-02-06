#include "SokobanGameState.h"

void AJuanIbargoitia_IUESokobanGameState::ResetCounters(int32 InTotalCrates)
{
	Moves = 0;
	TotalCrates = FMath::Max(0, InTotalCrates);
	CratesOnGoals = 0;
}

void AJuanIbargoitia_IUESokobanGameState::IncrementMoves()
{
	++Moves;
}

void AJuanIbargoitia_IUESokobanGameState::SetCratesOnGoals(int32 InCratesOnGoals)
{
	CratesOnGoals = FMath::Clamp(InCratesOnGoals, 0, TotalCrates);
}
