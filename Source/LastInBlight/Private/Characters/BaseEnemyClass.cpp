// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BaseEnemyClass.h"

#include "LastInBlight/LastInBlight.h"

void ABaseEnemyClass::HighlightActor()
{
	GetMesh()->SetRenderCustomDepth(true);
	WeaponR->SetRenderCustomDepth(true);
	WeaponL->SetRenderCustomDepth(true);

	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	WeaponR->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	WeaponL->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
}

void ABaseEnemyClass::UnHighlightActor()
{
	GetMesh()->SetRenderCustomDepth(false);
	WeaponR->SetRenderCustomDepth(false);
	WeaponL->SetRenderCustomDepth(false);
}

ABaseEnemyClass::ABaseEnemyClass()
{
	
	WeaponR = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponR");
	WeaponR->SetupAttachment(GetMesh(),FName("WeaponR"));
	WeaponR->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	WeaponL = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponL");
	WeaponL->SetupAttachment(GetMesh(),FName("WeaponL"));
	WeaponL->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility,ECR_Block);
	
}
