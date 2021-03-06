// Fill out your copyright notice in the Description page of Project Settings.


#include "ATelekinesis.h"
#include "mainPlayer.h"
// Sets default values
AATelekinesis::AATelekinesis()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("My Super Mesh"));
	Mesh->SetSimulatePhysics(true);
	Mesh->SetNotifyRigidBodyCollision(true);
	bPushed = false;
	FScriptDelegate delegate;
	delegate.BindUFunction(this, "onHit");
	Mesh->OnComponentHit.AddUnique(delegate);
	//PullTimeline = CreateDefaultSubobject<FTimeline>(TEXT("my Timeline"));
	//PullTimeline = CreateDefaultSubobject<FTimeline>(TEXT("pulltimeline"));
}

// Called when the game starts or when spawned
void AATelekinesis::BeginPlay()
{
	Super::BeginPlay();
	mainPlayer = Cast<AmainPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));

	if (Fcurve) {
		fpullProgress.BindUFunction(this, FName("pullProgress"));
		fPullEnd.BindUFunction(this, FName("pullEnd"));

		PullTimeline.AddInterpFloat(Fcurve, fpullProgress);
		PullTimeline.SetTimelineFinishedFunc(fPullEnd);
		PullTimeline.SetLooping(false);

		startLocation = endLocation = GetActorLocation();
		endLocation.Z += 100.f;
		
	}

	
}

// Called every frame
void AATelekinesis::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	PullTimeline.TickTimeline(DeltaTime);

	if (bPulled) {
		FVector target_location = mainPlayer->Scene->GetComponentLocation() - GetActorLocation();
		target_location = target_location.GetClampedToSize(0.f, 100.f);

		float mass = Mesh->GetMass();
		mass = FMath::GetMappedRangeValueClamped(FVector2D(1.f, 5.f), FVector2D(50.f, 700.f) , mass);
		Mesh->AddImpulse(target_location * mass);
	} 
	if (bPushed) {
		FVector target_location = pushTarget - GetActorLocation();
		target_location = target_location.GetClampedToSize(0.f, 100.f);

		float mass = Mesh->GetMass();
		mass = FMath::GetMappedRangeValueClamped(FVector2D(1.f, 5.f), FVector2D(50.f, 700.f), mass);
		Mesh->AddImpulse(target_location * mass);
	}
}


bool AATelekinesis::highlighted(bool bHighlighted) {
	Mesh->SetCustomDepthStencilValue(bHighlighted);
	return true;
}

void AATelekinesis::liftUp() {
	highlighted(false);
	FVector location = GetActorLocation();
	float liftHieght = 100.f;
	

}
void AATelekinesis::pull() {
	highlighted(false);
	startLocation = endLocation = GetActorLocation();
	endLocation.Z += 100.f;
	PullTimeline.PlayFromStart();
}
void AATelekinesis::push(FVector destination) {
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("I  pushedHit")));
	pushTarget = destination;
	bPushed = true;
	bPulled = false;
}

void AATelekinesis::onHit()
{
	if(bPushed){
	Mesh->SetEnableGravity(true);
	Mesh->SetLinearDamping(0.1f);
	bPushed = false;
	}
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("I Hit")));

}

void AATelekinesis::pullProgress(float progres)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("I Hit")));
	SetActorLocation(FMath::Lerp(startLocation, endLocation, progres));
}

void AATelekinesis::pullEnd()
{	
	Mesh->SetEnableGravity(false);
	Mesh->SetLinearDamping(20.0f);
	bPulled = true;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("My Location is: %s"), *mainPlayer->Scene->GetComponentTransform().GetLocation().ToString()));
	//GetWorld()->GetFirstPlayerController();
}
