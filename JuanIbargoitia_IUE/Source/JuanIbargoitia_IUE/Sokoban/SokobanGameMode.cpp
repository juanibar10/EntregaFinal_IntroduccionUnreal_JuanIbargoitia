#include "SokobanGameMode.h"

#include "SokobanCrate.h"
#include "SokobanGoal.h"
#include "SokobanUI.h"

#include "Kismet/GameplayStatics.h"

ASokobanGameMode::ASokobanGameMode()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ASokobanGameMode::BeginPlay()
{
	Super::BeginPlay();

	// Spawn UI (pattern reused from TwinStickGameMode)
	if (UIWidgetClass)
	{
		UIWidget = CreateWidget<USokobanUI>(UGameplayStatics::GetPlayerController(GetWorld(), 0), UIWidgetClass);
		if (UIWidget)
		{
			UIWidget->AddToViewport(0);
		}
	}

	BuildLevelState();

	if (UIWidget)
	{
		UIWidget->UpdateMoves(MoveCount);
		UIWidget->UpdateCratesRemaining(CratesRemaining);
	}
}

void ASokobanGameMode::NotifyPlayerAction()
{
	++MoveCount;
	if (UIWidget)
	{
		UIWidget->UpdateMoves(MoveCount);
	}

	RecomputeCratesRemaining();
	CheckVictory();
}

FVector ASokobanGameMode::GridToWorld(const FSokobanGridPos& P) const
{
	return GridOrigin + FVector(P.X * TileSize, P.Y * TileSize, 0.0f);
}

bool ASokobanGameMode::IsBlockedCell(const FSokobanGridPos& P) const
{
	return BlockedCells.Contains(P);
}

AActor* ASokobanGameMode::GetOccupantAt(const FSokobanGridPos& P) const
{
	if (const TObjectPtr<AActor>* Found = Occupancy.Find(P))
	{
		return Found->Get();
	}
	return nullptr;
}

void ASokobanGameMode::SetOccupantAt(const FSokobanGridPos& P, AActor* Occupant)
{
	if (!Occupant)
	{
		Occupancy.Remove(P);
		return;
	}
	Occupancy.Add(P, Occupant);
}

void ASokobanGameMode::ClearOccupantAt(const FSokobanGridPos& P, AActor* Occupant)
{
	AActor* Current = GetOccupantAt(P);
	if (Current == Occupant)
	{
		Occupancy.Remove(P);
	}
}

bool ASokobanGameMode::TryMoveCrate(const FSokobanGridPos& From, const FSokobanGridPos& Dir)
{
	ASokobanCrate* Crate = Cast<ASokobanCrate>(GetOccupantAt(From));
	if (!Crate)
	{
		return false;
	}

	const FSokobanGridPos To = From + Dir;
	if (IsBlockedCell(To) || GetOccupantAt(To) != nullptr)
	{
		return false;
	}

	ClearOccupantAt(From, Crate);
	Crate->GridPos = To;
	Crate->SetActorLocation(GridToWorld(To));
	SetOccupantAt(To, Crate);

	RecomputeCratesRemaining();
	return true;
}

void ASokobanGameMode::BuildLevelState()
{
	MoveCount = 0;
	bVictoryShown = false;
	Occupancy.Reset();
	Goals.Reset();
	Crates.Reset();

	TArray<AActor*> FoundGoals;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASokobanGoal::StaticClass(), FoundGoals);
	for (AActor* A : FoundGoals)
	{
		ASokobanGoal* G = Cast<ASokobanGoal>(A);
		if (!G) continue;
		Goals.Add(G->GridPos);
		G->SetActorLocation(GridToWorld(G->GridPos));
	}

	TArray<AActor*> FoundCrates;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASokobanCrate::StaticClass(), FoundCrates);
	for (AActor* A : FoundCrates)
	{
		ASokobanCrate* C = Cast<ASokobanCrate>(A);
		if (!C) continue;
		Crates.Add(C);
		C->SetActorLocation(GridToWorld(C->GridPos));
		SetOccupantAt(C->GridPos, C);
	}

	RecomputeCratesRemaining();
}

void ASokobanGameMode::RecomputeCratesRemaining()
{
	int32 OnGoals = 0;
	for (ASokobanCrate* C : Crates)
	{
		if (!IsValid(C)) continue;
		if (Goals.Contains(C->GridPos))
		{
			++OnGoals;
		}
	}

	const int32 TotalGoals = Goals.Num();
	// If no goals exist, avoid insta-victory; treat as all remaining.
	if (TotalGoals <= 0)
	{
		CratesRemaining = Crates.Num();
	}
	else
	{
		// Remaining goals not covered by a crate
		CratesRemaining = FMath::Max(0, TotalGoals - OnGoals);
	}

	if (UIWidget)
	{
		UIWidget->UpdateCratesRemaining(CratesRemaining);
	}
}

void ASokobanGameMode::CheckVictory()
{
	if (bVictoryShown)
	{
		return;
	}

	// Victory gate: needs at least one goal, and all goals are covered.
	if (Goals.Num() > 0 && CratesRemaining == 0)
	{
		bVictoryShown = true;
		if (UIWidget)
		{
			UIWidget->ShowVictory();
		}
	}
}
