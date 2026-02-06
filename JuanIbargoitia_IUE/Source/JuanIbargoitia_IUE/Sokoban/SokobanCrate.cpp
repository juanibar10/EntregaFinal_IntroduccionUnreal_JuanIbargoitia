#include "SokobanCrate.h"

AJuanIbargoitia_IUESokobanCrate::AJuanIbargoitia_IUESokobanCrate()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);

	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Mesh->SetCollisionObjectType(ECC_WorldDynamic);
	Mesh->SetCollisionResponseToAllChannels(ECR_Block);
}

void AJuanIbargoitia_IUESokobanCrate::StartMoveInterp(const FVector& From, const FVector& To, float Duration)
{
	bMoving = true;
	MoveElapsed = 0.f;
	MoveDuration = FMath::Max(0.01f, Duration);
	MoveFrom = From;
	MoveTo = To;
	SetActorLocation(From);
}

void AJuanIbargoitia_IUESokobanCrate::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!bMoving)
	{
		return;
	}

	MoveElapsed += DeltaSeconds;
	const float Alpha = FMath::Clamp(MoveElapsed / MoveDuration, 0.f, 1.f);
	const float Smoothed = FMath::InterpEaseInOut(0.f, 1.f, Alpha, 2.f);
	SetActorLocation(FMath::Lerp(MoveFrom, MoveTo, Smoothed));

	if (Alpha >= 1.f)
	{
		SetActorLocation(MoveTo);
		bMoving = false;
	}
}
