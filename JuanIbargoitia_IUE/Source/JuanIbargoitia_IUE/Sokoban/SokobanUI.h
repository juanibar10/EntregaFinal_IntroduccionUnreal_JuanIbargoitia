#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SokobanUI.generated.h"

UCLASS(Abstract)
class JUANIBARGOITIA_IUE_API USokobanUI : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent, Category="Sokoban|UI")
	void UpdateMoves(int32 Moves);

	UFUNCTION(BlueprintImplementableEvent, Category="Sokoban|UI")
	void UpdateCratesRemaining(int32 Remaining);

	UFUNCTION(BlueprintImplementableEvent, Category="Sokoban|UI")
	void ShowVictory();
};
