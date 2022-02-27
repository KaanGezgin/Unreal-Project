// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "HealthPotion.generated.h"


/**
 * 
 */
UCLASS()
class HACKANDSLASH_API AHealthPotion : public AItem
{
	GENERATED_BODY()

public:
	AHealthPotion();

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Healing")
		float HealingAmount;
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

};
