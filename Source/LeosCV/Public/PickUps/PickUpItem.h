// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "Components/SpotLightComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "Characters/MainPlayer.h"
#include "PickUpItem.generated.h"

UCLASS()
class LEOSCV_API APickUpItem : public AActor
{
	GENERATED_BODY()

public:
	//Actor components
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="Components")
	USphereComponent* ItemPickUpRangeCollision;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="Components")
	USphereComponent* ItemMagneticRangeCollision;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="Components")
	UStaticMeshComponent* ItemStaticMesh;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="Components")
	URotatingMovementComponent* RotatingComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="Components")
	USpotLightComponent* ItemLight;
	
	//Actor variables
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Effects")
	float EffectDuration;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="ItemSettings")
	bool bIsMagnetic;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="ItemSettings")
	bool bRotates;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="ItemSettings")
	bool bUpAndDown;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="ItemSettings")
	float RespawnTime;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="ItemData")
	AMainPlayer* ActorWhoPicked;

	//Code variables
	FTimerHandle RespawnableHandler;
	
	APickUpItem();
private:

	UFUNCTION()
	void CheckActorIsNoLongerOverlapping();

	UFUNCTION(BlueprintCallable, Category="ItemVisual")
	void ActivateItem(bool bActivate) const;
	
	UFUNCTION(Category="ItemCollision")
	void OnItemPickUpRangeOverlap(UPrimitiveComponent* OverlappedComponent, 
					  AActor* OtherActor, 
					  UPrimitiveComponent* OtherComp, 
					  int32 OtherBodyIndex, 
					  bool bFromSweep, 
					  const FHitResult &SweepResult );
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void ItemEffect();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
