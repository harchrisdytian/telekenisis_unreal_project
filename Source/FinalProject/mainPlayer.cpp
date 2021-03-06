// Fill out your copyright notice in the Description page of Project Settings.


#include "mainPlayer.h"

// Sets default values
AmainPlayer::AmainPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CameraRightOffset = 70.f;
	CameraUpOffset = 30.f;
	detectionRadius = 50.f;
	TelekinesisRange = 100000.f;

	objRef = nullptr;
	lastObjRef = nullptr;
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	bUseControllerRotationYaw = false;
	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("camera"));
	gimble = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	jumping = false;

	gimble->SocketOffset = (GetActorRightVector() * CameraRightOffset) + FVector(0, 0, CameraUpOffset);

	//Scene->SetupAttachment(RootComponent);
	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("scene"));
	Scene->AttachTo(GetMesh());
	gimble->AttachTo(RootComponent);

	gimble->TargetArmLength = 300.f;
	gimble->SetRelativeRotation(FRotator(-45.f, 0.f, 0.f));

	gimble->bEnableCameraLag = true;
	gimble->CameraLagSpeed = 2;
	gimble->CameraLagMaxDistance = 1.5f;

	gimble->bEnableCameraRotationLag = true;
	gimble->CameraRotationLagSpeed = 4;
	gimble->CameraLagMaxTimeStep = 1;

	camera->AttachTo(gimble, USpringArmComponent::SocketName);


}

// Called when the game starts or when spawned
void AmainPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AmainPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (jumping) {
		Jump();
	}
	//camera set the camera to the right of the charicter plz	
	gimble->SocketOffset = (GetActorRightVector() * CameraRightOffset) + FVector(0, 0, CameraUpOffset);
	if (isTelekinesis) {
		TestObjectsForTelekinesis();
	}
	
}

// Called to bind functionality to input
void AmainPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("HorizontalMovement", this, &AmainPlayer::VerticalMove);
	InputComponent->BindAxis("VerticalMovement", this, &AmainPlayer::HorizontalMove);
	InputComponent->BindAxis("HorizontalRotation", this, &AmainPlayer::HorizontalRotation);
	InputComponent->BindAxis("VerticalRotation", this, &AmainPlayer::VerticalRotation);
	InputComponent->BindAction("Jump", IE_Pressed, this, &AmainPlayer::CheckJump);
	InputComponent->BindAction("Jump", IE_Released, this, &AmainPlayer::CheckJump);
	InputComponent->BindAction("Telekinesis", IE_Pressed, this, &AmainPlayer::Telekinesis);
}


void AmainPlayer::CheckJump() {
	jumping = !jumping;

}

void AmainPlayer::HorizontalMove(float value) {
	if (value)
	{
		AddMovementInput(GetActorRightVector(), value);
	}
}

void AmainPlayer::VerticalMove(float value) {
	if (value)
	{
		AddMovementInput(GetActorForwardVector(), value);
	}
}
void AmainPlayer::HorizontalRotation(float value) {
	if (value) {

		AddActorLocalRotation(FRotator(0, value, 0));
	}
}
void AmainPlayer::VerticalRotation(float value) {

	float temp = gimble->GetRelativeRotation().Pitch + value;
	if (temp < 25 && temp > -65) {
		gimble->AddLocalRotation(FRotator(value, 0, 0));
	}
}

void AmainPlayer::Telekinesis() {
	isTelekinesis = !isTelekinesis; 
	if (isTelekinesis == true) {
		
		AmainPlayer::Push();
	}
	else {
		AmainPlayer::Pull();
	}
}

void AmainPlayer::Pull() {
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Purple ,TEXT("pull"));
	if (objRef != nullptr) {

		objRef->pull();
	}
}
void AmainPlayer::Push() {
	FVector forwardVec = camera->GetComponentLocation();// gets the camera location and ofsets it by the radius 
	FVector endVec = camera->GetComponentLocation() + (camera->GetForwardVector() * TelekinesisRange);
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Purple, TEXT("push"));
	FHitResult HitResult;
		if (GetWorld()->LineTraceSingleByChannel(HitResult,forwardVec,endVec,ECollisionChannel::ECC_Visibility)) {
			if (objRef != nullptr) {
				objRef->push(HitResult.ImpactPoint);
			}
	}
}
void AmainPlayer::TestObjectsForTelekinesis() {

	FVector forwardVec = camera->GetComponentLocation() + (camera->GetForwardVector() * detectionRadius);// gets the camera location and ofsets it by the radius 
	FVector endVec = camera->GetComponentLocation() + (camera->GetForwardVector() * TelekinesisRange);// gets the camera location and ofsets it by a pretty big number so that i can hit object far away 

	TArray<TEnumAsByte<EObjectTypeQuery>> objectTypesArray;// an array
	objectTypesArray.Add(EObjectTypeQuery::ObjectTypeQuery7);// adding the one that i called telekenisis 

	TArray<AActor*> ignoredActors;
	if (UKismetSystemLibrary::SphereTraceSingleForObjects(
		GetWorld(),//gets the world context 
		forwardVec, //is the start of the path
		endVec,// is the end of the path
		detectionRadius,// how big the sphere is that is has to trace
		objectTypesArray,// the types of object it is allowd to collid with,
		true, //false
		ignoredActors,// specific actors it can't collid with
		EDrawDebugTrace::None,// the line i use to make sure it works
		Fhit,// the object i am colliding with
		true // if i can collid with myself
	)) {

	
	
	if (lastObjRef != nullptr) {
		objRef->highlighted(false);
	}
	objRef = Cast<AATelekinesis>(Fhit.GetActor());
	if (objRef != nullptr) {
		
		objRef->highlighted(true);
	}
	lastObjRef = Cast<AATelekinesis>(Fhit.GetActor());
	}
}