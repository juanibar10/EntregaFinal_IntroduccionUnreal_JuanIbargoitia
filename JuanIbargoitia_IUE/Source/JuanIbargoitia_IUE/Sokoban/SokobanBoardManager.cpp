#include "SokobanBoardManager.h"

#include "EngineUtils.h"
#include "DrawDebugHelpers.h"
#include "SokobanCrate.h"
#include "SokobanGoal.h"
#include "SokobanGameState.h"
#include "SokobanWall.h"

AJuanIbargoitia_IUESokobanBoardManager::AJuanIbargoitia_IUESokobanBoardManager()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AJuanIbargoitia_IUESokobanBoardManager::BeginPlay()
{
	Super::BeginPlay();

	Origin = GetActorLocation();
	ScanLevel();
	RecomputeCratesOnGoals();
}

void AJuanIbargoitia_IUESokobanBoardManager::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!bDrawDebug)
	{
		return;
	}

	const FVector DebugHalfExtents(TileSize * 0.5f, TileSize * 0.5f, 20.f);
	const FVector DebugHalfExtentsGoal(TileSize * 0.45f, TileSize * 0.45f, 10.f);

	const FVector DebugOffset = bDebugDrawAtCellCorners
		? FVector(TileSize * 0.5f, TileSize * 0.5f, 0.f)
		: FVector::ZeroVector;

	for (const FIntPoint& Cell : WallCells)
	{
		DrawDebugBox(GetWorld(), CellToWorld(Cell) + DebugOffset, DebugHalfExtents, FColor::Red, false, -1.f, 0, 1.f);
	}

	for (const FIntPoint& Cell : GoalCells)
	{
		DrawDebugBox(GetWorld(), CellToWorld(Cell) + DebugOffset, DebugHalfExtentsGoal, FColor::Green, false, -1.f, 0, 1.f);
	}
}

FVector AJuanIbargoitia_IUESokobanBoardManager::CellToWorld(const FIntPoint& Cell) const
{
	return Origin + FVector((Cell.X + 0.5f) * TileSize, (Cell.Y + 0.5f) * TileSize, 0.f);
}

FIntPoint AJuanIbargoitia_IUESokobanBoardManager::WorldToCell(const FVector& World) const
{
	const FVector Local = World - Origin;

	const float CellX = (Local.X / TileSize) - 0.5f;
	const float CellY = (Local.Y / TileSize) - 0.5f;

	const int32 X = FMath::FloorToInt(CellX);
	const int32 Y = FMath::FloorToInt(CellY);

	return FIntPoint(X, Y);
}

void AJuanIbargoitia_IUESokobanBoardManager::ScanLevel()
{
	WallCells.Reset();
	GoalCells.Reset();
	CratesByCell.Reset();
	PlayerCells.Reset();

	for (TActorIterator<AJuanIbargoitia_IUESokobanWall> It(GetWorld()); It; ++It)
	{
		const FIntPoint Cell = WorldToCell(It->GetActorLocation());
		WallCells.Add(Cell);
		if (bSnapActorsToGridOnBeginPlay)
		{
			It->SetActorLocation(CellToWorld(Cell));
		}
	}
	for (TActorIterator<AJuanIbargoitia_IUESokobanGoal> It(GetWorld()); It; ++It)
	{
		const FIntPoint Cell = WorldToCell(It->GetActorLocation());
		GoalCells.Add(Cell);
		if (bSnapActorsToGridOnBeginPlay)
		{
			It->SetActorLocation(CellToWorld(Cell));
		}
	}
	for (TActorIterator<AJuanIbargoitia_IUESokobanCrate> It(GetWorld()); It; ++It)
	{
		AJuanIbargoitia_IUESokobanCrate* Crate = *It;
		const FIntPoint Cell = WorldToCell(Crate->GetActorLocation());
		Crate->GridCell = Cell;
		CratesByCell.Add(Cell, Crate);

		if (bSnapActorsToGridOnBeginPlay)
		{
			Crate->SetActorLocation(CellToWorld(Cell));
		}
	}

	CachedGS = GetWorld() ? GetWorld()->GetGameState<AJuanIbargoitia_IUESokobanGameState>() : nullptr;
	if (CachedGS.IsValid())
	{
		CachedGS->ResetCounters(CratesByCell.Num());
	}
}

AJuanIbargoitia_IUESokobanCrate* AJuanIbargoitia_IUESokobanBoardManager::FindCrateAtCell(const FIntPoint& Cell) const
{
	if (const TObjectPtr<AJuanIbargoitia_IUESokobanCrate>* Found = CratesByCell.Find(Cell))
	{
		return Found->Get();
	}
	return nullptr;
}

bool AJuanIbargoitia_IUESokobanBoardManager::IsWallAtCell(const FIntPoint& Cell) const
{
	return WallCells.Contains(Cell);
}

bool AJuanIbargoitia_IUESokobanBoardManager::IsGoalAtCell(const FIntPoint& Cell) const
{
	return GoalCells.Contains(Cell);
}

bool AJuanIbargoitia_IUESokobanBoardManager::IsCellBlockedForPlayer(const FIntPoint& Cell) const
{
	if (IsWallAtCell(Cell)) return true;
	if (FindCrateAtCell(Cell) != nullptr) return true;
	return false;
}

bool AJuanIbargoitia_IUESokobanBoardManager::IsCellBlockedForCrate(const FIntPoint& Cell) const
{
	if (IsWallAtCell(Cell)) return true;
	if (FindCrateAtCell(Cell) != nullptr) return true;
	if (PlayerCells.Contains(Cell)) return true;
	return false;
}

void AJuanIbargoitia_IUESokobanBoardManager::RegisterPlayerCell(const FIntPoint& Cell)
{
	PlayerCells.Add(Cell);
}

void AJuanIbargoitia_IUESokobanBoardManager::UnregisterPlayerCell(const FIntPoint& Cell)
{
	PlayerCells.Remove(Cell);
}

FSokobanStepResult AJuanIbargoitia_IUESokobanBoardManager::TryStep(const FIntPoint& PlayerCell, ESokobanDir Dir)
{
	FSokobanStepResult Result;

	const FIntPoint Delta = SokobanDirToDelta(Dir);
	const FIntPoint TargetCell = PlayerCell + Delta;

	if (IsWallAtCell(TargetCell))
	{
		return Result;
	}

	if (AJuanIbargoitia_IUESokobanCrate* Crate = FindCrateAtCell(TargetCell))
	{
		const FIntPoint BeyondCell = TargetCell + Delta;
		if (IsCellBlockedForCrate(BeyondCell))
		{
			return Result;
		}

		CratesByCell.Remove(TargetCell);
		CratesByCell.Add(BeyondCell, Crate);
		Crate->GridCell = BeyondCell;

		Result.bPushedCrate = true;
		Result.CrateFromCell = TargetCell;
		Result.CrateToCell = BeyondCell;
	}

	Result.bSuccess = true;
	Result.NewPlayerCell = TargetCell;

	return Result;
}

void AJuanIbargoitia_IUESokobanBoardManager::RecomputeCratesOnGoals()
{
	int32 OnGoals = 0;
	for (const TPair<FIntPoint, TObjectPtr<AJuanIbargoitia_IUESokobanCrate>>& Pair : CratesByCell)
	{
		if (GoalCells.Contains(Pair.Key))
		{
			++OnGoals;
		}
	}

	if (!CachedGS.IsValid())
	{
		CachedGS = GetWorld() ? GetWorld()->GetGameState<AJuanIbargoitia_IUESokobanGameState>() : nullptr;
	}
	if (CachedGS.IsValid())
	{
		CachedGS->SetCratesOnGoals(OnGoals);
	}
}
