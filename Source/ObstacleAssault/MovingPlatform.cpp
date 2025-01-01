// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();

	// LogTemp => what type of log category we are doing.
	// Display => Level of the log
	// Text => Log text
	UE_LOG(LogTemp, Display, TEXT("Platform named %s has started play."), *GetName())
	UE_LOG(LogTemp, Display, TEXT("Configured Moved Distance: %f"), MoveDistance)

	// Different levels for logs.
	// UE_LOG(LogTemp, Warning, TEXT(""))
	// UE_LOG(LogTemp, Error, TEXT(""))
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MovePlatform(DeltaTime);
	RotatePlatform(DeltaTime);
}

void AMovingPlatform::RotatePlatform(float DeltaTime)
{
	AddActorLocalRotation(DeltaTime * RotationVelocity);
}

void AMovingPlatform::MovePlatform(float DeltaTime)
{
	FVector CurrentLocation = GetActorLocation();

	CurrentLocation += (MoveVelocity * DeltaTime);

	float distance = FVector::Dist(StartLocation, CurrentLocation);

	if(distance > MoveDistance)
	{
		float OverShoot = distance - MoveDistance;
		UE_LOG(LogTemp, Display, TEXT("Platform overshot by  %f"), OverShoot)

		// for fix the overshot problem.
		FVector MoveDirection = MoveVelocity.GetSafeNormal();
		StartLocation += (MoveDirection * MoveDistance);
		SetActorLocation(StartLocation);
		MoveVelocity = -MoveVelocity;
	}

	SetActorLocation(CurrentLocation);
}