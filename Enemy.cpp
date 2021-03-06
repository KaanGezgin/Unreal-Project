// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "EnemyController.h"
#include "BehaviorTree/BlackboardComponent.h"


// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	FVector Location = GetActorLocation();
	EnemyController = Cast<AEnemyController>(GetController());
	EnemyController->GetBlackboardComponent()->SetValueAsVector(TEXT("PatrolPoint1"), PatrolPoint1 + Location);
	EnemyController->GetBlackboardComponent()->SetValueAsVector(TEXT("PatrolPoint2"), PatrolPoint2 + Location);
	EnemyController->GetBlackboardComponent()->SetValueAsVector(TEXT("PatrolPoint3"), PatrolPoint3 + Location);
	EnemyController->GetBlackboardComponent()->SetValueAsVector(TEXT("PatrolPoint4"), PatrolPoint4 + Location);

}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemy::SetIsAccelerating(bool bAccelerating)
{
	//bIsAccelerating = bAccelerating;
	bIsAccelerating = bAccelerating;
}