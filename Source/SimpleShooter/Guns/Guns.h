// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Guns.generated.h"

UCLASS()
class SIMPLESHOOTER_API AGuns : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGuns();

	void PullTrigger();

	UPROPERTY(EditAnywhere)
	float FireDelay;
	UPROPERTY(EditAnywhere)
	float Recoil;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Components
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;
	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* Mesh;
	UPROPERTY(EditAnywhere)
	UParticleSystem* MuzzleFlash;
	UPROPERTY(EditAnywhere)
	UParticleSystem* HitImpact;
	UPROPERTY(EditAnywhere)
	float MaxRange = 3000;
	UPROPERTY(EditAnywhere)
	float DamageDelt = 34;
	UPROPERTY(EditAnywhere)
	USoundBase* MuzzleSound;
	UPROPERTY(EditAnywhere)
	USoundBase* ImpactSound;
	
	// functions
	bool GunTrace(FHitResult &Hit, FVector &ShotDirection);
	AController* GetOwnerController() const;

	// Variables
	FVector Location;
	FRotator Rotation;
	FVector EndPoint;
};
