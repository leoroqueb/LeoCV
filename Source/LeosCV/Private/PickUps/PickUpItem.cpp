// Fill out your copyright notice in the Description page of Project Settings.


#include "PickUps/PickUpItem.h"

// Sets default values
APickUpItem::APickUpItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ItemStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("ItemMesh"));
	ItemPickUpRangeCollision = CreateDefaultSubobject<USphereComponent>(FName("PickUpRangeCollision"));
	ItemMagneticRangeCollision = CreateDefaultSubobject<USphereComponent>(FName("MagneticRangeCollision"));
	RotatingComponent = CreateDefaultSubobject<URotatingMovementComponent>(FName("RotatingComponent"));
	ItemLight = CreateDefaultSubobject<USpotLightComponent>(FName("ItemLight"));
	
	ItemStaticMesh->SetupAttachment(RootComponent);
	ItemPickUpRangeCollision->SetupAttachment(ItemStaticMesh);
	ItemMagneticRangeCollision->SetupAttachment(ItemStaticMesh);
	ItemLight->SetupAttachment(ItemStaticMesh);
	
	ItemStaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// Default values
	bRotates = true;
	bUpAndDown = true;
}

void APickUpItem::ActivateItem(const bool bActivate) const
{
	if(IsValid(this)){
		ItemStaticMesh->SetVisibility(bActivate);
		ItemMagneticRangeCollision->SetActive(bActivate);
		ItemPickUpRangeCollision->SetActive(bActivate);
		ItemLight->SetVisibility(bActivate);
	}
}

void APickUpItem::OnItemPickUpRangeOverlap(UPrimitiveComponent* OverlappedComponent, 
					  AActor* OtherActor, 
					  UPrimitiveComponent* OtherComp, 
					  int32 OtherBodyIndex, 
					  bool bFromSweep, 
					  const FHitResult &SweepResult )
{
	// Check actor who overlapped is player
	ActorWhoPicked = Cast<ALeosCVCharacter>(OtherActor);
	if(ActorWhoPicked)
	{
		if(RespawnTime > 0)
		{
			// Hide everything for 'RespawnTime' secs
			ActivateItem(false);
			
			ItemEffect();
			GetWorldTimerManager().SetTimer(RespawnableHandler, this, &APickUpItem::CheckActorIsNoLongerOverlapping,
				GetWorld()->GetDeltaSeconds()/2, true, RespawnTime);
			
		}else
		{
			ItemEffect();
			Destroy();
		}
	}
}

void APickUpItem::CheckActorIsNoLongerOverlapping()
{
	if(!IsOverlappingActor(ActorWhoPicked))
	{
		GetWorldTimerManager().ClearTimer(RespawnableHandler);
		ActivateItem(true);
	}
}

// Called when the game starts or when spawned
void APickUpItem::BeginPlay()
{
	Super::BeginPlay();

	ItemPickUpRangeCollision->OnComponentBeginOverlap.AddDynamic(this, &APickUpItem::OnItemPickUpRangeOverlap);

	if(bRotates)
	{
		RotatingComponent->SetActive(true);
	}
	
}

// Called every frame
void APickUpItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

