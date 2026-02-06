#include "SokobanCrate.h"
#include "Components/StaticMeshComponent.h"

ASokobanCrate::ASokobanCrate()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
