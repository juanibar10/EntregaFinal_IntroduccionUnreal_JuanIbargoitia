#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SceneComponent.h"
#include "SokobanGoal.generated.h"

UCLASS()
class AJuanIbargoitia_IUESokobanGoal : public AActor
{
	GENERATED_BODY()

public:
	AJuanIbargoitia_IUESokobanGoal();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sokoban")
	TObjectPtr<USceneComponent> Root;
};
