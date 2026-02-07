#include "SokobanCrate.h"

AJuanIbargoitia_IUESokobanCrate::AJuanIbargoitia_IUESokobanCrate()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);

	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Mesh->SetCollisionObjectType(ECC_WorldDynamic);
	Mesh->SetCollisionResponseToAllChannels(ECR_Block);
}

void AJuanIbargoitia_IUESokobanCrate::StartMoveInterp(const FVector& From, const FVector& To, float Duration)
{
	bMoving = false;
	MoveElapsed = 0.f;
	MoveDuration = FMath::Max(0.01f, Duration);
	MoveFrom = From;
	MoveTo = To;
	SetActorLocation(From);
}