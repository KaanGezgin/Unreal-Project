// Fill out your copyright notice in the Description page of Project Settings.


#include "ChaphterSwitch.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "MainCharacter.h"
#include "SwitchInterface.h"
#include "SwitchTargetV2.h"

// Sets default values
AChaphterSwitch::AChaphterSwitch()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	RootComponent = TriggerBox;
	TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	TriggerBox->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	TriggerBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	TriggerBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	TriggerBox->SetBoxExtent(FVector(62.f, 62.f, 62.f));
	FloorSwitch = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FloorSwitch"));
	FloorSwitch->SetupAttachment(GetRootComponent());
	Door = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));
	Door->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void AChaphterSwitch::BeginPlay()
{
	Super::BeginPlay();
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AChaphterSwitch::OnOverlapBegin);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &AChaphterSwitch::OnOverlapEnd);
	InitialDoorLocation = Door->GetComponentLocation();
	InitialSwitchLocation = FloorSwitch->GetComponentLocation();

}

// Called every frame
void AChaphterSwitch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AChaphterSwitch::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMainCharacter* MainCharacter = Cast<AMainCharacter>(OtherActor);
	if (MainCharacter)
	{
		ActivateFloorSwitch();
	}
}
void AChaphterSwitch::OnOverlapEnd(UPrimitiveComponent* OverllapedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AMainCharacter* MainCharacter = Cast<AMainCharacter>(OtherActor);
	if (MainCharacter)
	{
		DeactivateFloorSwitch();
	}
}

void AChaphterSwitch::UpdateFloorSwitchLocations(float DoorLocation, float SwitchLocation)
{
	FVector NewDoorLocation = InitialDoorLocation;
	NewDoorLocation.Z += DoorLocation;
	Door->SetWorldLocation(NewDoorLocation);
	FVector NewSwitchLocation = InitialSwitchLocation;
	NewSwitchLocation.Z += SwitchLocation;
	FloorSwitch->SetWorldLocation(NewSwitchLocation);
}

void AChaphterSwitch::ActivateSwitchTargets()
{
	for (ASwitchTargetV2* SwitchTarget : SwitchTargets)
	{
		ISwitchInterface* Interface = Cast<ISwitchInterface>(SwitchTarget);
		if (Interface)
		{
			SwitchTarget->Activate_Implementation();
		}
	}
}