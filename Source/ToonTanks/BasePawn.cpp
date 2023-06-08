// Fill out your copyright notice in the Description page of Project Settings.

#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile.h"
#include "Engine/World.h"

// Sets default values
ABasePawn::ABasePawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));
	RootComponent = CapsuleComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	BaseMesh->SetupAttachment(CapsuleComp);

	Turrent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurrentMesh"));
	Turrent->SetupAttachment(BaseMesh);

	ProjectileSpwan = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpwanPoint"));
	ProjectileSpwan->SetupAttachment(Turrent);
}

// Called when the game starts or when spawned
void ABasePawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABasePawn::HandleDestruction()
{
}

void ABasePawn::RotateTurrent(FVector LookAtTarget)
{
	FVector ToTarget = LookAtTarget - Turrent->GetComponentLocation();
	FRotator LookAtRotaion = FRotator(0.f, ToTarget.Rotation().Yaw, 0.f);
	Turrent->SetWorldRotation(FMath::RInterpTo(Turrent->GetComponentRotation(), LookAtRotaion, UGameplayStatics::GetWorldDeltaSeconds(this), 5.f));
}

void ABasePawn::fire()
{
	FVector Location = ProjectileSpwan->GetComponentLocation();
	FRotator Rotation = ProjectileSpwan->GetComponentRotation();
	auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, Location, Rotation);
	Projectile->SetOwner(this);
}
