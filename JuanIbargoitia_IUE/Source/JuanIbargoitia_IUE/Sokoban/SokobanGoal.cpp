#include "SokobanGoal.h"

AJuanIbargoitia_IUESokobanGoal::AJuanIbargoitia_IUESokobanGoal()
{
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
}
