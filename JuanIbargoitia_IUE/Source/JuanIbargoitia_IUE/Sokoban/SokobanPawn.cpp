#include "SokobanPawn.h"

#include "SokobanCrate.h"
#include "SokobanGameMode.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

ASokobanPawn::ASokobanPawn()
{
	PrimaryActorTick.bCanEverTick = false;

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	SetRootComponent(Capsule);
	Capsule->InitCapsuleSize(34.0f, 88.0f);
	Capsule->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Capsule->SetCollisionResponseToAllChannels(ECR_Ignore);

	Visual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Visual"));
	Visual->SetupAttachment(Capsule);
	Visual->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(Capsule);
	CameraBoom->SetUsingAbsoluteRotation(true);
	CameraBoom->TargetArmLength = 800.0f;
	CameraBoom->SetRelativeRotation(FRotator(-60.0f, 0.0f, 0.0f));
	CameraBoom->bDoCollisionTest = false;

	TopDownCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCamera->bUsePawnControlRotation = false;

	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

void ASokobanPawn::BeginPlay()
{
	Super::BeginPlay();

	// Snap to grid on start
	SetActorLocation(GridToWorld(GridPos));
}

void ASokobanPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("Sokoban_Up", IE_Pressed, this, &ASokobanPawn::MoveUp);
	PlayerInputComponent->BindAction("Sokoban_Down", IE_Pressed, this, &ASokobanPawn::MoveDown);
	PlayerInputComponent->BindAction("Sokoban_Left", IE_Pressed, this, &ASokobanPawn::MoveLeft);
	PlayerInputComponent->BindAction("Sokoban_Right", IE_Pressed, this, &ASokobanPawn::MoveRight);
}

void ASokobanPawn::MoveUp() { TryMove(FSokobanGridPos(0, 1)); }
void ASokobanPawn::MoveDown() { TryMove(FSokobanGridPos(0, -1)); }
void ASokobanPawn::MoveLeft() { TryMove(FSokobanGridPos(-1, 0)); }
void ASokobanPawn::MoveRight() { TryMove(FSokobanGridPos(1, 0)); }

bool ASokobanPawn::TryMove(const FSokobanGridPos& Dir)
{
	ASokobanGameMode* GM = GetSokobanGM();
	if (!GM)
	{
		return false;
	}

	const FSokobanGridPos Target = GridPos + Dir;
	if (GM->IsBlockedCell(Target))
	{
		return false;
	}

	AActor* Occupant = GM->GetOccupantAt(Target);
	if (Occupant)
	{
		// Only crates are pushable.
		if (!GM->TryMoveCrate(Target, Dir))
		{
			return false;
		}
	}

	GridPos = Target;
	SetActorLocation(GridToWorld(GridPos));
	GM->NotifyPlayerAction();
	return true;
}

float ASokobanPawn::GetTileSize() const
{
	if (TileSizeOverride > 0.0f)
	{
		return TileSizeOverride;
	}
	if (const ASokobanGameMode* GM = GetSokobanGM())
	{
		return GM->TileSize;
	}
	return 200.0f;
}

FVector ASokobanPawn::GetGridOrigin() const
{
	if (!GridOriginOverride.IsNearlyZero())
	{
		return GridOriginOverride;
	}
	if (const ASokobanGameMode* GM = GetSokobanGM())
	{
		return GM->GridOrigin;
	}
	return FVector::ZeroVector;
}

FVector ASokobanPawn::GridToWorld(const FSokobanGridPos& P) const
{
	return GetGridOrigin() + FVector(P.X * GetTileSize(), P.Y * GetTileSize(), 0.0f);
}

ASokobanGameMode* ASokobanPawn::GetSokobanGM() const
{
	return Cast<ASokobanGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
}
