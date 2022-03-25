// Fill out your copyright notice in the Description page of Project Settings.


#include "Turtle.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "TurtleController.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Sound/SoundCue.h"

// Sets default values
ATurtle::ATurtle()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATurtle::BeginPlay()
{
	Super::BeginPlay();	

}

// Called every frame
void ATurtle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATurtle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATurtle::StartDestroyEffect(FVector Loc)
{
	if (DestroyParticles)
	{
		SpawnedDestroyParticles = UGameplayStatics::SpawnEmitterAtLocation
		(
			GetWorld(),
			DestroyParticles,
			GetActorLocation(),
			FRotator(0.f),
			FVector(2.f),
			true
		);

		if (DestroyCue)
		{
			UGameplayStatics::PlaySound2D(this, DestroyCue);
		}
	}
}

void ATurtle::SetFinishLocation(FVector Target)
{
	if (TurtleController)
	{
		TurtleController->GetBlackboardComponent()->SetValueAsVector(TEXT("FinishLocation"), Target);
	}
}

void ATurtle::SetupTurtleProperties(ETurtleType TurtleType)
{
	const FString TurtleTablePath{ TEXT("DataTable'/Game/_Game/DataTable/TurtleDataTable.TurtleDataTable'") };
	UDataTable* TurtleTableObject = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, *TurtleTablePath));

	if (TurtleTableObject)
	{
		FTurtleDataTable* TurtleDataRow = nullptr;

		// Row switch
		switch (TurtleType)
		{
		case ETurtleType::ETT_FirstType:
			TurtleDataRow = TurtleTableObject->FindRow<FTurtleDataTable>(FName("FirstType"), TEXT(""));
			break;
		case ETurtleType::ETT_SecondType:
			TurtleDataRow = TurtleTableObject->FindRow<FTurtleDataTable>(FName("SecondType"), TEXT(""));
			break;
		case ETurtleType::ETT_ThirdType:
			TurtleDataRow = TurtleTableObject->FindRow<FTurtleDataTable>(FName("ThirdType"), TEXT(""));
			break;
		}

		if (TurtleDataRow)
		{
			BehaviorTree = TurtleDataRow->BehaviorTree;
			TurtleController = Cast<ATurtleController>(GetController());
			if (TurtleController)
			{
				TurtleController->RunBehaviorTree(BehaviorTree);
				TurtleController->GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetActorLocation());
			}

			//  TODO: Add diff options
		}

	}
}

