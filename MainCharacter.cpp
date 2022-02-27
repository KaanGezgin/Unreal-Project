// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Animation/AnimInstance.h"
#include "MainPlayerController.h"
#include "CountessSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "NavigationSystem.h"
#include "NavigationPath.h"
#include "RotatingActor.h"
#include "DrawDebugHelpers.h"


// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f;

	CameraBoom->bUsePawnControlRotation = true;
	
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	CameraBoom->bUsePawnControlRotation = false;

	//Dont rotate when the controller rotates. Just affect the camera
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	
	Health = 85.f;
	MaxHealth = 100.f;

}
void AMainCharacter::SetHealth(float Amount)
{
	if (Amount > MaxHealth)
	{
		Health = MaxHealth;
	}
	else if (Amount < 0)
	{
		Health = 0;
	}
	else
	{
		Health = Amount;
	}
}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	MainPlayerController = Cast<AMainPlayerController>(GetController());
	TSubclassOf<AActor>WorldClassObject = ARotatingActor::StaticClass();
	TArray<AActor*>ActorsOfClass;
	UGameplayStatics::GetAllActorsOfClass(this, WorldClassObject, ActorsOfClass);
	if (ActorsOfClass.Num() > 0)
	{
		UNavigationPath* NavPath = UNavigationSystemV1::FindPathToActorSynchronously(this, GetActorLocation(), ActorsOfClass[0]);
		if (NavPath->PathPoints.Num() > 0)
		{
			for (auto pt : NavPath->PathPoints)
			{
				DrawDebugSphere(GetWorld(), pt, 20.f, 12, FColor::Red, true);
			}
		}
	}


}
void AMainCharacter::MoveForward(float Value) {


	if ((Controller != NULL) && (Value != 0.0f)) {
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AMainCharacter::MoveRight(float Value) {
  /*FVector Right = GetActorRightVector();
	AddMovementInput(Right, Value);
	*/
	if ((Controller != NULL) && (Value != 0.0f)) {
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}


// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMainCharacter::MoveRight);
	PlayerInputComponent->BindAxis("MoveForward", this, &AMainCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("LMBDown", IE_Pressed, this, &AMainCharacter::LMBDown);
	PlayerInputComponent->BindAction("ESC", IE_Pressed, this, &AMainCharacter::ESCDown);
}

void AMainCharacter::LMBDown() {
	
	
	if (bAttacking)
		return;
	bAttacking = true;
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();

	if (AnimInstance && CharacterAttackMontage)
	{
		AnimInstance->Montage_Play(CharacterAttackMontage);
	}
	
}
void AMainCharacter::ESCDown()
{
	if (MainPlayerController)
	{
		MainPlayerController->TogglePauseMenu();
	}
}

void AMainCharacter::SaveGame()
{
	UCountessSaveGame* SaveGameInstance = Cast<UCountessSaveGame>(UGameplayStatics::CreateSaveGameObject(UCountessSaveGame::StaticClass()));
	SaveGameInstance->Health = Health;
	SaveGameInstance->MaxHealth = MaxHealth;
	SaveGameInstance->WorldLocation = GetActorLocation();
	SaveGameInstance->WorldRotation = GetActorRotation();
	UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveGameInstance->PlayerName, SaveGameInstance->UserSlot);
}

void AMainCharacter::LoadGame()
{
	UCountessSaveGame* LoadGameInstance = Cast<UCountessSaveGame>(UGameplayStatics::CreateSaveGameObject(UCountessSaveGame::StaticClass()));
	LoadGameInstance = Cast<UCountessSaveGame>(UGameplayStatics::LoadGameFromSlot(LoadGameInstance->PlayerName, LoadGameInstance->UserSlot));
	Health = LoadGameInstance->Health;
	MaxHealth = LoadGameInstance->MaxHealth;
	SetActorLocation(LoadGameInstance->WorldLocation);
	SetActorRotation(LoadGameInstance->WorldRotation);
}

void AMainCharacter::ToggleAllRotators()
{
	TSubclassOf<AActor> WorldClassObject = ARotatingActor::StaticClass();
	TArray<AActor*>ActorsOfClass;
	UGameplayStatics::GetAllActorsOfClass(this, WorldClassObject, ActorsOfClass);
	for (AActor* Actor : ActorsOfClass)
	{
		ARotatingActor* RotatingActor = Cast<ARotatingActor>(Actor);
		if (RotatingActor)
		{
			RotatingActor->ToggleRotate();
		}
	}
	//RotateDelegate.ExecuteIfBound();
}