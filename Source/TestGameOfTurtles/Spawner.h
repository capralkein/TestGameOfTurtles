// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Turtle.h"
#include "Spawner.generated.h"

UCLASS()
class TESTGAMEOFTURTLES_API ASpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Defaults, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* SpawnerMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Defaults, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* FinishMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Defaults, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ATurtle> TurtleToSpawn;

	UPROPERTY(EditAnywhere, Category = Defaults, meta = (AllowPrivateAccess = true, MakeEditWidget = true))
	FVector TargetPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Defaults, meta = (AllowPrivateAccess = "true"))
	ETurtleType TypeToAppear;

	void StartTeleportEffect(FVector Loc);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Teleport, meta = (AllowPrivateAccess = true))
	class UParticleSystem* TeleportParticles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Teleport, meta = (AllowPrivateAccess = "true"))
	class USoundCue* SpawnCue;

	class UParticleSystemComponent* SpawnedTeleportParticles;


public:
	UFUNCTION(BlueprintCallable)
	void SpawnTurtle();	

	FORCEINLINE ETurtleType GetTypeToAppear() const { return TypeToAppear; }

};