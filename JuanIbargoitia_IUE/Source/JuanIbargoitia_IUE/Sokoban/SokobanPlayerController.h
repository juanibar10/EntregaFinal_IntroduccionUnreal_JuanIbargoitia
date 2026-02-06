#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SokobanPlayerController.generated.h"

UCLASS()
class JUANIBARGOITIA_IUE_API ASokobanPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ASokobanPlayerController();

	virtual void BeginPlay() override;
};
