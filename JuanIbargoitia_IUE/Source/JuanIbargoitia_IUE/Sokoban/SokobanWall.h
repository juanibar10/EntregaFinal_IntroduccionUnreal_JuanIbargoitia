#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "SokobanWall.generated.h"

UCLASS()
class AJuanIbargoitia_IUESokobanWall : public AActor
{
	GENERATED_BODY()

public:
	AJuanIbargoitia_IUESokobanWall();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sokoban")
	TObjectPtr<UStaticMeshComponent> Mesh;
};
