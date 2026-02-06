#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "SokobanGameState.generated.h"

UCLASS()
class AJuanIbargoitia_IUESokobanGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "Sokoban")
	int32 GetMoves() const { return Moves; }

	UFUNCTION(BlueprintPure, Category = "Sokoban")
	int32 GetTotalCrates() const { return TotalCrates; }

	UFUNCTION(BlueprintPure, Category = "Sokoban")
	int32 GetCratesOnGoals() const { return CratesOnGoals; }

	UFUNCTION(BlueprintPure, Category = "Sokoban")
	int32 GetCratesRemaining() const { return FMath::Max(0, TotalCrates - CratesOnGoals); }

	void ResetCounters(int32 InTotalCrates);
	void IncrementMoves();
	void SetCratesOnGoals(int32 InCratesOnGoals);

private:
	UPROPERTY()
	int32 Moves = 0;

	UPROPERTY()
	int32 TotalCrates = 0;

	UPROPERTY()
	int32 CratesOnGoals = 0;
};
