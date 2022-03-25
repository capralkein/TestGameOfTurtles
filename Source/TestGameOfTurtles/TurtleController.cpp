// Fill out your copyright notice in the Description page of Project Settings.


#include "TurtleController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Kismet/GameplayStatics.h"
#include "Turtle.h"

ATurtleController::ATurtleController()
{
	BlackBoardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackBoardComponent"));
	check(BlackBoardComponent);

	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
	check(BehaviorTreeComponent);
}

void ATurtleController::BeginPlay()
{
	Super::BeginPlay();


}

void ATurtleController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (InPawn == nullptr) return;

	ATurtle* Turtle = Cast<ATurtle>(InPawn);
	if (Turtle)
	{
		if (Turtle->GetBehaviorTree())
		{
			BlackBoardComponent->InitializeBlackboard(*(Turtle->GetBehaviorTree()->BlackboardAsset));
		}
	}
}