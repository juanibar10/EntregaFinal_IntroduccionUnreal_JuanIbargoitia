// Minimal Sokoban grid helper types
#pragma once

#include "CoreMinimal.h"
#include "SokobanTypes.generated.h"

USTRUCT(BlueprintType)
struct FSokobanGridPos
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Sokoban")
	int32 X = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Sokoban")
	int32 Y = 0;

	FSokobanGridPos() = default;
	FSokobanGridPos(int32 InX, int32 InY) : X(InX), Y(InY) {}

	FORCEINLINE bool operator==(const FSokobanGridPos& Other) const { return X == Other.X && Y == Other.Y; }
	FORCEINLINE bool operator!=(const FSokobanGridPos& Other) const { return !(*this == Other); }

	FORCEINLINE FSokobanGridPos operator+(const FSokobanGridPos& Other) const { return FSokobanGridPos(X + Other.X, Y + Other.Y); }
};

FORCEINLINE uint32 GetTypeHash(const FSokobanGridPos& P)
{
	return HashCombine(::GetTypeHash(P.X), ::GetTypeHash(P.Y));
}
