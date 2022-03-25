// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Engine/DataTable.h"
#include "Turtle.generated.h"

USTRUCT(BlueprintType)
struct FTurtleDataTable : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBehaviorTree* BehaviorTree;

	//  TODO: Add diff options
};

UENUM(BlueprintType)
enum class ETurtleType : uint8
{
	ETT_FirstType UMETA(DisplayName = "FirstType"),
	ETT_SecondType UMETA(DisplayName = "SecondType"),
	ETT_ThirdType UMETA(DisplayName = "ThirdType"),

	ETT_MAX UMETA(DisplayName = "DefaultMax")
};

UCLASS()
class TESTGAMEOFTURTLES_API ATurtle : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATurtle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	class ATurtleController* TurtleController;

	UPROPERTY(EditAnywhere, Category = "BehaviorTree", meta = (AllowPrivateAccess = true))
	UBehaviorTree* BehaviorTree;

	UFUNCTION(BlueprintCallable)
	void StartDestroyEffect(FVector Loc);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Teleport, meta = (AllowPrivateAccess = true))
	class UParticleSystem* DestroyParticles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Teleport, meta = (AllowPrivateAccess = "true"))
	class USoundCue* DestroyCue;

	class UParticleSystemComponent* SpawnedDestroyParticles;

public:

	FORCEINLINE UBehaviorTree* GetBehaviorTree() const { return BehaviorTree; }
	void SetFinishLocation(FVector Target);
	void SetupTurtleProperties(ETurtleType TurtleType);
};
