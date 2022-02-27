// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"

//DECLARE_DELEGATE(FRotateDelegate);
DECLARE_DYNAMIC_DELEGATE_RetVal_OneParam(float, FDynamicRotateDelegate, float, RotationSpeed);

UCLASS()

class HACKANDSLASH_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()


public:
	// Sets default values for this character's properties
	AMainCharacter();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Controller")
	class AMainPlayerController* MainPlayerController;


	FORCEINLINE float GetHealth() {
		return Health;
	}
	void SetHealth(float Amount);

	FORCEINLINE float GetMaxHealth() {
		return MaxHealth;
	}
	FORCEINLINE void SetMaxHealth(float Amount) {
		MaxHealth = Amount;
	}
	//FRotateDelegate RotateDelegate;

	void ESCDown();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void MoveForward(float Value);
	void MoveRight(float value);
	void LMBDown();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Combat")
		bool bAttacking;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Anims");
		class UAnimMontage* CharacterAttackMontage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerStats")
		float Health;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PlayerStats")
		float MaxHealth;
	UFUNCTION(BlueprintCallable)
		void SaveGame();
	UFUNCTION(BlueprintCallable)
		void LoadGame();
	UFUNCTION(BlueprintCallable)
		void ToggleAllRotators();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
