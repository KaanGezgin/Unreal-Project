// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ChaphterSwitch.generated.h"

UCLASS()
class HACKANDSLASH_API AChaphterSwitch : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChaphterSwitch();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Floor Switch");
	class UBoxComponent* TriggerBox;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Floor Switch");
	class UStaticMeshComponent* FloorSwitch;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Floor Switch");
	class UStaticMeshComponent* Door;
	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnOverlapEnd(UPrimitiveComponent* OverllapedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION(BlueprintImplementableEvent, Category = "Floor Switch")
		void ActivateFloorSwitch();
	UFUNCTION(BlueprintImplementableEvent, Category = "Floor Switch")
		void DeactivateFloorSwitch();
	UFUNCTION(BlueprintCallable, Category = "Floor Switch")
		void UpdateFloorSwitchLocations(float DoorLocation, float SwitchLocation);
	UPROPERTY(BlueprintReadWrite, Category = "Floor Switch")
		FVector InitialSwitchLocation;
	UPROPERTY(BlueprintReadWrite, Category = "Floor Switch")
		FVector InitialDoorLocation;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Switch")
		TArray<class ASwitchTargetV2*> SwitchTargets;
	UFUNCTION(BlueprintCallable)
		void ActivateSwitchTargets();

		 

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
