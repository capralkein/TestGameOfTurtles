// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawner.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Sound/SoundCue.h"

// Sets default values
ASpawner::ASpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SpawnerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SpawnerMesh"));
	SetRootComponent(SpawnerMesh);

	FinishMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FinishMesh"));
	FinishMesh->SetVisibility(false);

	// When TurtleToSpawn is missing after rebuilding
	if (!TurtleToSpawn)
	{
		UBlueprint* blueprint = Cast<UBlueprint>(StaticLoadObject(UObject::StaticClass(), NULL, TEXT("Blueprint'/Game/_Game/Turtle/BP_Turtle.BP_Turtle'")));
		TSubclassOf<class UObject> MyItemBlueprint = (UClass*)(blueprint->GeneratedClass);
		// :TOFIX
		TurtleToSpawn = MyItemBlueprint;
	}
}

// Called when the game starts or when spawned
void ASpawner::BeginPlay()
{
	Super::BeginPlay();

	
}

// Called every frame
void ASpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

void ASpawner::StartTeleportEffect(FVector Loc)
{
	if (TeleportParticles)
	{
		SpawnedTeleportParticles = UGameplayStatics::SpawnEmitterAtLocation
		(
			GetWorld(),
			TeleportParticles,
			GetActorLocation(),
			FRotator(0.f),
			FVector(2.f),
			true
		);

		if (SpawnCue)
		{
			UGameplayStatics::PlaySound2D(this, SpawnCue);
		}
	}
}

void ASpawner::SpawnTurtle()
{
	StartTeleportEffect(GetActorLocation());

	FActorSpawnParameters SpawnParams;
	ATurtle* SpawnedActorRef = GetWorld()->SpawnActor<ATurtle>(TurtleToSpawn, GetActorLocation(), GetActorRotation(), SpawnParams);

	if (SpawnedActorRef)
	{
		const FVector WorldTargetPoint = UKismetMathLibrary::TransformLocation(GetActorTransform(), TargetPoint);
		SpawnedActorRef->SetupTurtleProperties(TypeToAppear);
		SpawnedActorRef->SetFinishLocation(WorldTargetPoint);
		if (FinishMesh)
		{
			FinishMesh->SetRelativeLocation(TargetPoint);
			FinishMesh->SetVisibility(true);
		}
	}
	else
	{
		// Cant spawn
		UE_LOG(LogTemp, Warning, TEXT("Can't spawn turtle"));
	}
}

