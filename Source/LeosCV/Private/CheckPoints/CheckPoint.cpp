// Fill out your copyright notice in the Description page of Project Settings.


#include "CheckPoints/CheckPoint.h"

#include "GameManagement/LeoCVSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "Characters/MainPlayer.h"
#include "LeosCV/LeosCVGameMode.h"

// Sets default values
ACheckPoint::ACheckPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CheckPointMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("CheckPointMesh"));
	CheckPointTrigger = CreateDefaultSubobject<UBoxComponent>(FName("CheckPointTrigger"));
	CheckPointSpawnArrow = CreateDefaultSubobject<UArrowComponent>(FName("SpawnArrow"));

	CheckPointMesh->SetupAttachment(RootComponent);
	CheckPointTrigger->SetupAttachment(CheckPointMesh);
	CheckPointSpawnArrow->SetupAttachment(CheckPointMesh);

}

void ACheckPoint::OnStepOnCheckPoint(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(Cast<AMainPlayer>(OtherActor))
	{
		ALeosCVGameMode* GM = Cast<ALeosCVGameMode>(UGameplayStatics::GetGameMode(this));
		GM->SaveGame(CheckPointSpawnArrow->GetComponentTransform());
	}
}

// Called when the game starts or when spawned
void ACheckPoint::BeginPlay()
{
	Super::BeginPlay();
	CheckPointTrigger->OnComponentBeginOverlap.AddDynamic(this, &ACheckPoint::OnStepOnCheckPoint);
}

// Called every frame
void ACheckPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

