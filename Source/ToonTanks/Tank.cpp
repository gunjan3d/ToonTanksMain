// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

ATank::ATank()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);


}


void ATank::BeginPlay()
{
	Super::BeginPlay();
	TankPlayerController = Cast<APlayerController>(GetController());

}




// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FHitResult HitResult;
	if(TankPlayerController)
	{
		TankPlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility,false,HitResult);

		RotateTurrent(HitResult.ImpactPoint);
		// DrawDebugSphere(GetWorld(),HitResult.ImpactPoint,25.f,12,FColor::Red,false,-1.f);

	}

}

void ATank::HandleDestruction()
{
	Super::HandleDestruction();
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
}


// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("MoveForward"),this , &ATank::Move);
	PlayerInputComponent->BindAxis(TEXT("Turn"),this, &ATank::Turn);
	PlayerInputComponent->BindAction(TEXT("Fire"),IE_Pressed,this,&ATank::fire);
	
}




void ATank::Move(float val)
{
	FVector DeltaLocation(0.f);
	DeltaLocation.X = val * MovementSpeed * UGameplayStatics::GetWorldDeltaSeconds(this);
	AddActorLocalOffset(DeltaLocation,true);

}





void ATank::Turn(float val)
{
	FRotator DeltaRotation(0.f);
	DeltaRotation.Yaw = val * RotationSpeed * UGameplayStatics::GetWorldDeltaSeconds(this);
	AddActorLocalRotation(DeltaRotation);
}







