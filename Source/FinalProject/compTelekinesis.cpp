// Fill out your copyright notice in the Description page of Project Settings.


#include "compTelekinesis.h"

// Sets default values for this component's properties
UcompTelekinesis::UcompTelekinesis()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UcompTelekinesis::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UcompTelekinesis::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UcompTelekinesis::highlighted(bool bhighlighted) {
//	UPrimitiveComponent::SetCustomDepthStencilValue(bhighlighted);
	return true;
}