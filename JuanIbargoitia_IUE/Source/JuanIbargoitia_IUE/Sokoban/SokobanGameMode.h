#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SokobanTypes.h"
#include "SokobanGameMode.generated.h"

class USokobanUI;
class ASokobanCrate;
class ASokobanGoal;

UCLASS()
class JUANIBARGOITIA_IUE_API ASokobanGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASokobanGameMode();

	virtual void BeginPlay() override;

	// Grid config
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Sokoban|Grid", meta=(ClampMin="10.0"))
	float TileSize = 200.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Sokoban|Grid")
	FVector GridOrigin = FVector::ZeroVector;

	// UI
	UPROPERTY(EditAnywhere, Category="Sokoban|UI")
	TSubclassOf<USokobanUI> UIWidgetClass;

	// Gameplay stats
	UFUNCTION(BlueprintCallable, Category="Sokoban|Stats")
	int32 GetMoveCount() const { return MoveCount; }

	UFUNCTION(BlueprintCallable, Category="Sokoban|Stats")
	int32 GetCratesRemaining() const { return CratesRemaining; }

	// Called by pawn after a successful action.
	void NotifyPlayerAction();

	// Grid helpers
	FVector GridToWorld(const FSokobanGridPos& P) const;

	// Occupancy queries (walls are provided as blocked cells)
	UFUNCTION(BlueprintCallable, Category="Sokoban|Grid")
	bool IsBlockedCell(const FSokobanGridPos& P) const;

	AActor* GetOccupantAt(const FSokobanGridPos& P) const;
	void SetOccupantAt(const FSokobanGridPos& P, AActor* Occupant);
	void ClearOccupantAt(const FSokobanGridPos& P, AActor* Occupant);

	bool TryMoveCrate(const FSokobanGridPos& From, const FSokobanGridPos& Dir);

protected:
	void BuildLevelState();
	void RecomputeCratesRemaining();
	void CheckVictory();

protected:
	UPROPERTY(EditAnywhere, Category="Sokoban|Grid")
	TArray<FSokobanGridPos> BlockedCells;

	UPROPERTY()
	TObjectPtr<USokobanUI> UIWidget;

	UPROPERTY()
	TArray<TObjectPtr<ASokobanCrate>> Crates;

	UPROPERTY()
	TSet<FSokobanGridPos> Goals;

	UPROPERTY()
	TMap<FSokobanGridPos, TObjectPtr<AActor>> Occupancy;

	int32 MoveCount = 0;
	int32 CratesRemaining = 0;
	bool bVictoryShown = false;
};
