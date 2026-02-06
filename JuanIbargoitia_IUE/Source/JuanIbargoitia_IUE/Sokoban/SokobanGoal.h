#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SokobanTypes.h"
#include "SokobanGoal.generated.h"

UCLASS()
class JUANIBARGOITIA_IUE_API ASokobanGoal : public AActor
{
	GENERATED_BODY()

public:
	ASokobanGoal();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Sokoban")
	FSokobanGridPos GridPos;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	TObjectPtr<class UStaticMeshComponent> Mesh;
};
