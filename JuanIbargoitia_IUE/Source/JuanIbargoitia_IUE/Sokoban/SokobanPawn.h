#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SokobanTypes.h"
#include "SokobanPawn.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UCapsuleComponent;
class UStaticMeshComponent;

UCLASS()
class JUANIBARGOITIA_IUE_API ASokobanPawn : public APawn
{
	GENERATED_BODY()

public:
	ASokobanPawn();

	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Sokoban")
	FSokobanGridPos GridPos;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Sokoban")
	float TileSizeOverride = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Sokoban")
	FVector GridOriginOverride = FVector::ZeroVector;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	TObjectPtr<UCapsuleComponent> Capsule;

	// Visible capsule mesh
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	TObjectPtr<UStaticMeshComponent> Visual;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	TObjectPtr<UCameraComponent> TopDownCamera;

protected:
	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();

	bool TryMove(const FSokobanGridPos& Dir);
	float GetTileSize() const;
	FVector GetGridOrigin() const;

	FVector GridToWorld(const FSokobanGridPos& P) const;

	class ASokobanGameMode* GetSokobanGM() const;
};
