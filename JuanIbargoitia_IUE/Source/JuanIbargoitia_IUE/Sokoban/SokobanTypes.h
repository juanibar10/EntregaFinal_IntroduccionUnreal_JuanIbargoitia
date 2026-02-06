#pragma once

#include "CoreMinimal.h"
#include "SokobanTypes.generated.h"

UENUM(BlueprintType)
enum class ESokobanDir : uint8
{
	Up,
	Down,
	Left,
	Right
};

USTRUCT(BlueprintType)
struct FSokobanStepResult
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	bool bSuccess = false;

	UPROPERTY(BlueprintReadOnly)
	bool bPushedCrate = false;

	UPROPERTY(BlueprintReadOnly)
	FIntPoint NewPlayerCell = FIntPoint::ZeroValue;

	UPROPERTY(BlueprintReadOnly)
	FIntPoint CrateFromCell = FIntPoint::ZeroValue;

	UPROPERTY(BlueprintReadOnly)
	FIntPoint CrateToCell = FIntPoint::ZeroValue;
};

inline FIntPoint SokobanDirToDelta(ESokobanDir Dir)
{
	switch (Dir)
	{
	case ESokobanDir::Up: return FIntPoint(1, 0);
	case ESokobanDir::Down: return FIntPoint(-1, 0);
	case ESokobanDir::Left: return FIntPoint(0, -1);
	case ESokobanDir::Right: return FIntPoint(0, 1);
	default: return FIntPoint::ZeroValue;
	}
}