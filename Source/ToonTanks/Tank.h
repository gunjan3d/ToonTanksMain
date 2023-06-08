// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()
public:
	ATank();

	void HandleDestruction();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// void HandleDestruction();
	APlayerController* GetPlayerController() const{return TankPlayerController;}
private:
	UPROPERTY(VisibleAnywhere,meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Camera;


	UPROPERTY(VisibleAnywhere,meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArm;


	UPROPERTY(EditAnywhere,meta = (AllowPrivateAccess="true"))
	float MovementSpeed = 500.f;

	
	UPROPERTY(EditAnywhere,meta = (AllowPrivateAccess="true"))
	float RotationSpeed = 100.f;

	class APlayerController* TankPlayerController;
	
	void Move(float val);
	void Turn(float val);

};
