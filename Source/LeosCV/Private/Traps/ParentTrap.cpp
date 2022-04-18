// Fill out your copyright notice in the Description page of Project Settings.


#include "Traps/ParentTrap.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Characters/MainPlayer.h"

// Sets default values
AParentTrap::AParentTrap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TrapMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("TrapMesh"));
	TrapTrigger = CreateDefaultSubobject<UBoxComponent>(FName("TrapTrigger"));

	TrapMesh->SetupAttachment(RootComponent);
	TrapTrigger->SetupAttachment(TrapMesh);

	bIsActive = false;

}

// Called when the game starts or when spawned
void AParentTrap::BeginPlay()
{
	Super::BeginPlay();
	
}

void AParentTrap::OnPlayerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AMainPlayer* DetectedPlayer = Cast<AMainPlayer>(OtherActor); DetectedPlayer && !bIsActive)
	{
		// Prevent multicast
		bIsActive = true;
		if(Damage > 0)
		{
			UGameplayStatics::ApplyDamage(DetectedPlayer, Damage, nullptr,
				this, nullptr);

			// Fix: Prevents to trap a player which is already dead
			if(DetectedPlayer->Health > 0)
			{
				TrapEffect(DetectedPlayer);
			}
		}
		
		GetWorldTimerManager().SetTimer(ActiveTrapTimer, this, &AParentTrap::RestartTrap,
										0.1, false, CoolDownTime);
	}
}

void AParentTrap::RestartTrap()
{
	bIsActive = false;
	GetWorldTimerManager().ClearTimer(ActiveTrapTimer);
}


// Called every frame
void AParentTrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TrapTrigger->OnComponentBeginOverlap.AddDynamic(this, &AParentTrap::OnPlayerBeginOverlap);

}

