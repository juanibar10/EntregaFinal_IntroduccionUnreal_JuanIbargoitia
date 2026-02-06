#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SokobanTypes.h"
#include "SokobanPawn.generated.h"

class UCapsuleComponent;
class UStaticMeshComponent;
class UCameraComponent;
class USpringArmComponent;
class AJuanIbargoitia_IUESokobanBoardManager;
class AJuanIbargoitia_IUESokobanCrate;
class AJuanIbargoitia_IUESokobanGameState;

UCLASS()
class AJuanIbargoitia_IUESokobanPawn : public APawn
{
	GENERATED_BODY()

public:
	AJuanIbargoitia_IUESokobanPawn();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	bool IsMoving() const { return bMoving; }
	FIntPoint GetGridCell() const { return GridCell; }

	bool RequestStep(ESokobanDir Dir);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sokoban")
	TObjectPtr<UCapsuleComponent> Capsule;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sokoban")
	TObjectPtr<UStaticMeshComponent> Visual;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sokoban")
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sokoban")
	TObjectPtr<UCameraComponent> TopDownCamera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sokoban")
	float StepDuration = 0.12f;

private:
	TWeakObjectPtr<AJuanIbargoitia_IUESokobanBoardManager> Board;
	TWeakObjectPtr<AJuanIbargoitia_IUESokobanGameState> CachedGS;

	FIntPoint GridCell = FIntPoint::ZeroValue;

	bool bMoving = false;
	float MoveElapsed = 0.f;
	FVector MoveFrom = FVector::ZeroVector;
	FVector MoveTo = FVector::ZeroVector;

	TWeakObjectPtr<AJuanIbargoitia_IUESokobanCrate> MovingCrate;
	FVector CrateFrom = FVector::ZeroVector;
	FVector CrateTo = FVector::ZeroVector;

	void StartStep(const FVector& From, const FVector& To);
};
