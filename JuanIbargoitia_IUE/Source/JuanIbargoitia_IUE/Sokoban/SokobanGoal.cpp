#include "SokobanGoal.h"
#include "Components/StaticMeshComponent.h"

ASokobanGoal::ASokobanGoal()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
