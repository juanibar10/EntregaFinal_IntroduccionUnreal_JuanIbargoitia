#include "SokobanPawn.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EngineUtils.h"

#include "SokobanBoardManager.h"
#include "SokobanCrate.h"
#include "SokobanGameState.h"

AJuanIbargoitia_IUESokobanPawn::AJuanIbargoitia_IUESokobanPawn()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	SetRootComponent(Capsule);
	Capsule->InitCapsuleSize(42.f, 96.f);
	Capsule->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Capsule->SetCollisionObjectType(ECC_Pawn);
	Capsule->SetCollisionResponseToAllChannels(ECR_Block);

	Visual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Visual"));
	Visual->SetupAttachment(Capsule);
	Visual->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(Capsule);
	CameraBoom->SetUsingAbsoluteRotation(true);
	CameraBoom->TargetArmLength = 900.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false;

	TopDownCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCamera->bUsePawnControlRotation = false;

	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

void AJuanIbargoitia_IUESokobanPawn::BeginPlay()
{
	Super::BeginPlay();

	// find board manager
	for (TActorIterator<AJuanIbargoitia_IUESokobanBoardManager> It(GetWorld()); It; ++It)
	{
		Board = *It;
		break;
	}

	if (Board.IsValid())
	{
		GridCell = Board->WorldToCell(GetActorLocation());
		SetActorLocation(Board->CellToWorld(GridCell));
		Board->RegisterPlayerCell(GridCell);
	}

	CachedGS = GetWorld() ? GetWorld()->GetGameState<AJuanIbargoitia_IUESokobanGameState>() : nullptr;
}

void AJuanIbargoitia_IUESokobanPawn::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!bMoving)
	{
		return;
	}

	MoveElapsed += DeltaSeconds;
	const float Alpha = FMath::Clamp(MoveElapsed / FMath::Max(0.01f, StepDuration), 0.f, 1.f);
	const float Smoothed = FMath::InterpEaseInOut(0.f, 1.f, Alpha, 2.f);
	SetActorLocation(FMath::Lerp(MoveFrom, MoveTo, Smoothed));

	if (MovingCrate.IsValid())
	{
		MovingCrate->SetActorLocation(FMath::Lerp(CrateFrom, CrateTo, Smoothed));
	}

	if (Alpha >= 1.f)
	{
		SetActorLocation(MoveTo);
		if (MovingCrate.IsValid())
		{
			MovingCrate->SetActorLocation(CrateTo);
		}

		bMoving = false;
		MovingCrate = nullptr;

		if (Board.IsValid())
		{
			Board->RecomputeCratesOnGoals();
		}
	}
}

void AJuanIbargoitia_IUESokobanPawn::StartStep(const FVector& From, const FVector& To)
{
	bMoving = true;
	MoveElapsed = 0.f;
	MoveFrom = From;
	MoveTo = To;
	SetActorLocation(From);
}

bool AJuanIbargoitia_IUESokobanPawn::RequestStep(ESokobanDir Dir)
{
	if (bMoving || !Board.IsValid())
	{
		return false;
	}

	const FSokobanStepResult Step = Board->TryStep(GridCell, Dir);
	if (!Step.bSuccess)
	{
		return false;
	}

	// update occupancy for player
	Board->UnregisterPlayerCell(GridCell);
	GridCell = Step.NewPlayerCell;
	Board->RegisterPlayerCell(GridCell);

	if (!CachedGS.IsValid())
	{
		CachedGS = GetWorld() ? GetWorld()->GetGameState<AJuanIbargoitia_IUESokobanGameState>() : nullptr;
	}
	if (CachedGS.IsValid())
	{
		CachedGS->IncrementMoves();
	}

	// Setup crate movement visuals if pushed
	MovingCrate = nullptr;
	if (Step.bPushedCrate)
	{
		if (AJuanIbargoitia_IUESokobanCrate* Crate = Board->FindCrateAtCell(Step.CrateToCell))
		{
			MovingCrate = Crate;
			CrateFrom = Board->CellToWorld(Step.CrateFromCell);
			CrateTo = Board->CellToWorld(Step.CrateToCell);
		}
	}

	const FVector From = GetActorLocation();
	const FVector To = Board->CellToWorld(GridCell);
	StartStep(From, To);
	return true;
}
