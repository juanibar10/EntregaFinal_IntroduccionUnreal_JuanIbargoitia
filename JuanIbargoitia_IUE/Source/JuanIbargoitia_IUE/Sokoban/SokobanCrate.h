#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SokobanTypes.h"
#include "SokobanCrate.generated.h"

UCLASS()
class JUANIBARGOITIA_IUE_API ASokobanCrate : public AActor
{
	GENERATED_BODY()

public:
	ASokobanCrate();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Sokoban")
	FSokobanGridPos GridPos;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	TObjectPtr<class UStaticMeshComponent> Mesh;
};
