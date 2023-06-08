// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Missle"));
	RootComponent = ProjectileMesh;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
	ProjectileMovementComponent->MaxSpeed = 1300.f;
	ProjectileMovementComponent->InitialSpeed = 1000.f;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComponent,FVector NormalImpulse,const FHitResult & Hit)
{
	// UE_LOG(LogTemp, Warning, TEXT("Hit Sucessfull"));
	auto MyOwner = GetOwner();
	if(MyOwner==nullptr)
	{
		Destroy();
		return;
	}
	auto MyOnwerIsntigator = MyOwner->GetInstigatorController();
	auto DamageTypeClass = UDamageType::StaticClass();
	if(OtherActor && OtherActor != this && OtherActor != MyOwner)
	{
		UGameplayStatics::ApplyDamage(OtherActor,Damage,MyOnwerIsntigator,this,DamageTypeClass);
		
		if(HitParticles)UGameplayStatics::SpawnEmitterAtLocation(this,HitParticles,GetActorLocation(),GetActorRotation());
		Destroy();
	}
	Destroy();

}
