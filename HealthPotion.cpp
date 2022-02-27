// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthPotion.h"
#include <HackAndSlash/MainCharacter.h>

AHealthPotion::AHealthPotion() 
{
	HealingAmount = 20.f;
}

void AHealthPotion::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("AHealthPotion::OnOverlapBegin"));
	AMainCharacter* MainCharacter = Cast<AMainCharacter>(OtherActor);
	if (MainCharacter) 
	{
		MainCharacter->SetHealth(MainCharacter->GetHealth() + HealingAmount);
	}
	Super::OnOverlapBegin(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

}