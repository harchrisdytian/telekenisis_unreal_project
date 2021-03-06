// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h" 
#include "Kismet/GameplayStatics.h"
#include "ATelekinesis.generated.h"

class AmainPlayer;
UCLASS()
class FINALPROJECT_API AATelekinesis : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AATelekinesis();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	bool highlighted(bool bhighlighted);

	void liftUp();
	void pull();
	void push(FVector destination);
	UFUNCTION()
		void onHit();
	UPROPERTY()
		FVector startLocation;
	UPROPERTY()
		FVector endLocation;
	UPROPERTY()
		FVector pushTarget;
	UPROPERTY(VisibleAnywhere)
		UMeshComponent* Mesh;
	UPROPERTY(EditAnywhere, Category = "Timeline")
		UCurveFloat* Fcurve;

	AmainPlayer* mainPlayer;
	
	FTimeline PullTimeline;
	UFUNCTION()
		void pullProgress(float progres);
	UFUNCTION()
		void pullEnd();
	

	FOnTimelineEvent fPullEnd{};
	FOnTimelineFloat fpullProgress{};
	
	bool bPulled;
	bool bPushed;
};
