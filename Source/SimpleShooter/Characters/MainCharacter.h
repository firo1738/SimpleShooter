// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"

class AGuns;
UCLASS()
class SIMPLESHOOTER_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	UFUNCTION(BlueprintPure)
	bool IsDead() const;
	UFUNCTION(BlueprintPure)
	float HealthPercent() const;
	UFUNCTION(BlueprintPure)
	int Ammunitions();
	UFUNCTION(BlueprintPure)
	int MaxAmmu();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Called when character is shot at
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const &DamageEvent, class AController *EventInstigator, AActor *DamageCauser) override;

	void Shoot();
	void Reload();
	void ResetFire();
	void StartFire();
	void StopRecoil();

private:
	// Components
	void MoveForward(float AxisValue);
	void MoveSide(float AxisValue);
	void ContLookUp(float AxisValue);
	void ContLookSide(float AxisValue);

	// Variables
	float RotationRate = 50.f;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGuns> GunClass; 
	UPROPERTY()
	AGuns* Gun;
	UPROPERTY(EditDefaultsOnly)
	float MaxHealth = 100;
	UPROPERTY(VisibleAnywhere)
	float Health;
	UPROPERTY(EditAnywhere)
	int Ammo= 30;
	UPROPERTY(EditAnywhere)
	int MaxAmmo;
	bool IsRecoilling;
	FTimerHandle Timer;
	FTimerHandle RecoilTimer;
};
