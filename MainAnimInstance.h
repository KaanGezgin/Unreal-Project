// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MainAnimInstance.generated.h"


/**
 * 
 */
UCLASS()
class HACKANDSLASH_API UMainAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

		
public:

	virtual void NativeInitializeAnimation()override;
	UFUNCTION(BlueprintCallable, Category = AnimationProperites)
		void UpdateAnimationProperties(float DeltaTime);
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
		float MovementSpeed;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
		bool bIsInAir;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
		bool bIsAcceleration;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
		float YawDelta;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
		FRotator RotationLastFrame;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
		class APawn* Pawn;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Movement)
		class AMainCharacter* Main;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
		class AEnemy* Enemy;


};
