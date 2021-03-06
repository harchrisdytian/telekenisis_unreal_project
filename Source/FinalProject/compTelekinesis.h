// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ITelekenisis.h"
#include "compTelekinesis.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FINALPROJECT_API UcompTelekinesis : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UcompTelekinesis();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	bool highlighted(bool bHighlighted);
		
};
