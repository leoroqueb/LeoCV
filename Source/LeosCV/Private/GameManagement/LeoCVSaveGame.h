// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "LeoCVSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class ULeoCVSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, Category="PlayerBasics")
	FTransform PlayerPosition;

	UPROPERTY(VisibleAnywhere, Category="PlayerBasics")
	float PlayerHealth;

	UPROPERTY(VisibleAnywhere, Category="PlayerBasics")
	int PlayerLifes;
	
};
