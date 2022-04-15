// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "LeosCV/LeosCVCharacter.h"
#include "ParentTrap.generated.h"

UCLASS()
class LEOSCV_API AParentTrap : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AParentTrap();

	// Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UStaticMeshComponent* TrapMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UBoxComponent* TrapTrigger;

	//Actor variables
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="TrapStatus")
	bool bIsActive;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="TrapSettings")
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="TrapSettings")
	float CoolDownTime;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="TrapSettings")
	float EffectDuration;

	FTimerHandle ActiveTrapTimer;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void OnPlayerBeginOverlap(UPrimitiveComponent* OverlappedComponent, 
					  AActor* OtherActor, 
					  UPrimitiveComponent* OtherComp, 
					  int32 OtherBodyIndex, 
					  bool bFromSweep, 
					  const FHitResult &SweepResult);

	UFUNCTION()
	void RestartTrap();

	UFUNCTION(BlueprintImplementableEvent)
	void TrapEffect(ALeosCVCharacter* Player);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
