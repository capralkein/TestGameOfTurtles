// Fill out your copyright notice in the Description page of Project Settings.


#include "TurtleAnimInstance.h"
#include "Turtle.h"

void UTurtleAnimInstance::UpdateAnimationProperties(float DeltaTime)
{
	if (Turtle == nullptr)
	{
		Turtle = Cast<ATurtle>(TryGetPawnOwner());
	}

	if (Turtle)
	{
		FVector Velocity{ Turtle->GetVelocity() };
		Velocity.Z = 0.f;
		Speed = Velocity.Size();
	}
}