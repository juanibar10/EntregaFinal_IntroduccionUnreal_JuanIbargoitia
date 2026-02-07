#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SokobanTypes.h"
#include "SokobanBoardManager.generated.h"

class AJuanIbargoitia_IUESokobanCrate;
class AJuanIbargoitia_IUESokobanGoal;
class AJuanIbargoitia_IUESokobanGameState;

UCLASS()
class AJuanIbargoitia_IUESokobanBoardManager : public AActor
{
	GENERATED_BODY()

public:
	AJuanIbargoitia_IUESokobanBoardManager();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sokoban")
	float TileSize = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sokoban")
	bool bSnapActorsToGridOnBeginPlay = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sokoban")
	bool bDrawDebug = true;

	bool bDebugDrawAtCellCorners = true;

	UFUNCTION(BlueprintPure, Category = "Sokoban")
	FVector CellToWorld(const FIntPoint& Cell) const;

	UFUNCTION(BlueprintPure, Category = "Sokoban")
	FIntPoint WorldToCell(const FVector& World) const;

	FSokobanStepResult TryStep(const FIntPoint& PlayerCell, ESokobanDir Dir);

	AJuanIbargoitia_IUESokobanCrate* FindCrateAtCell(const FIntPoint& Cell) const;
	bool IsWallAtCell(const FIntPoint& Cell) const;
	bool IsGoalAtCell(const FIntPoint& Cell) const;
	bool IsCellBlockedForPlayer(const FIntPoint& Cell) const;
	bool IsCellBlockedForCrate(const FIntPoint& Cell) const;

	void RegisterPlayerCell(const FIntPoint& Cell);
	void UnregisterPlayerCell(const FIntPoint& Cell);

	void ScanLevel();
	void RecomputeCratesOnGoals();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

private:
	FVector Origin = FVector::ZeroVector;

	TSet<FIntPoint> WallCells;
	TSet<FIntPoint> GoalCells;
	TMap<FIntPoint, TObjectPtr<AJuanIbargoitia_IUESokobanCrate>> CratesByCell;
	TSet<FIntPoint> PlayerCells;

	TWeakObjectPtr<AJuanIbargoitia_IUESokobanGameState> CachedGS;
};
