// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Spawner.h"
#include "Turtle.h"
#include "Kismet/GameplayStatics.h"

ABasePlayerController::ABasePlayerController()
{

}

void ABasePlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (HUDOverlayClass)
	{
		HUDOverlay = CreateWidget<UUserWidget>(this, HUDOverlayClass);
		if (HUDOverlay)
		{
			HUDOverlay->AddToViewport();
			HUDOverlay->SetVisibility(ESlateVisibility::Visible);
		}
	}

	// Create Array of all spawners
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawner::StaticClass(), Spawners);

	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
}

void ABasePlayerController::ButtonPressed(int32 Index)
{
	const ETurtleType Type = static_cast<ETurtleType>(Index);

	for (auto Spawner : Spawners)
	{
		ASpawner* SpawnToActivate = Cast<ASpawner>(Spawner);
		if (SpawnToActivate)
		{
			if (SpawnToActivate->GetTypeToAppear() == Type)
			{
				SpawnToActivate->SpawnTurtle();
			}
		}
	}
}