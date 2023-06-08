// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditDefaultsOnly,Category = "Combact")
	class UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(VisibleAnywhere,Category = "Combact")
	class UProjectileMovementComponent* ProjectileMovementComponent;
	
	
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComponent,FVector NormalImpulse,const FHitResult &Hit);
	UPROPERTY(EditAnywhere, meta =(AllowPrivateAccess="true"))
	float Damage = 100.f;

	UPROPERTY(EditAnywhere, meta =(AllowPrivateAccess="true"),Category = "Combact")
	class UParticleSystem* HitParticles;
};
