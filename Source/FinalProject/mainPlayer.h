// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Character.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/KismetArrayLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/World.h"
#include "ATelekinesis.h"
#include "UObject/Object.h"
//#include "Blueprint/UserWidget.h"
#include "mainPlayer.generated.h"

UCLASS()
class FINALPROJECT_API AmainPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AmainPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
private:
	void HorizontalMove(float value);
	void VerticalMove(float value);
	void HorizontalRotation(float value);
	void VerticalRotation(float value);
	void CheckJump();
	void Telekinesis();
	void Push();
	void Pull();
	void TestObjectsForTelekinesis();

public:
	UPROPERTY(EditAnywhere)
		USceneComponent* Scene;
	UPROPERTY()
		bool jumping;
	UPROPERTY()
		float detectionRadius;
	UPROPERTY()
		float TelekinesisRange;
	UPROPERTY()
		bool isTelekinesis;
	UPROPERTY()
		float CameraRightOffset;
	UPROPERTY()
		float CameraUpOffset;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera )
		UCameraComponent* camera;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		USpringArmComponent* gimble;
	UPROPERTY()
		float arm_length = 300.0f;
	UPROPERTY()
		FHitResult Fhit;
	UPROPERTY()
		AATelekinesis* objRef;
	UPROPERTY()
		AATelekinesis* lastObjRef;

};
