#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "SokobanCrate.generated.h"

UCLASS()
class AJuanIbargoitia_IUESokobanCrate : public AActor
{
	GENERATED_BODY()

public:
	AJuanIbargoitia_IUESokobanCrate();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sokoban")
	TObjectPtr<UStaticMeshComponent> Mesh;

	FIntPoint GridCell = FIntPoint::ZeroValue;

	void StartMoveInterp(const FVector& From, const FVector& To, float Duration);
	bool IsMoving() const { return bMoving; }

protected:
	virtual void Tick(float DeltaSeconds) override;

private:
	bool bMoving = false;
	float MoveElapsed = 0.f;
	float MoveDuration = 0.15f;
	FVector MoveFrom = FVector::ZeroVector;
	FVector MoveTo = FVector::ZeroVector;
};
