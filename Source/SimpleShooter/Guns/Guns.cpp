// Fill out your copyright notice in the Description page of Project Settings.


#include "Guns.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/Gameplaystatics.h"
#include "DrawDebugHelpers.h"

// Sets default values
AGuns::AGuns()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
}

void AGuns::PullTrigger()
{
		UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));
		UGameplayStatics::SpawnSoundAttached(MuzzleSound, Mesh, TEXT("MuzzleFlashSocket"));
		// UGameplayStatics::SpawnEmitterAttached(ShotTrace, Mesh, TEXT("GunTrace"));
		
		FHitResult Hit;

		FVector ShotDirection;

		bool bSuccess = GunTrace(Hit, ShotDirection);

		if (bSuccess)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitImpact, Hit.Location, ShotDirection.Rotation());
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactSound, Hit.Location);
		}

		AActor* HitActor = Hit.GetActor();
		if (HitActor != nullptr)
		{
			FPointDamageEvent DamageEvent(DamageDelt, Hit, ShotDirection, nullptr);
			AController* OwnerController = GetOwnerController();
			HitActor->TakeDamage(DamageDelt, DamageEvent, OwnerController, this);
		}
}

// Called when the game starts or when spawned
void AGuns::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AGuns::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool AGuns::GunTrace(FHitResult &Hit, FVector &ShotDirection) 
{
	AController* OwnerController = GetOwnerController();
	if (OwnerController == nullptr)
	{
		return false;
	}
	
	OwnerController->GetPlayerViewPoint(Location, Rotation);

	EndPoint = Location + Rotation.Vector() * MaxRange;

	ShotDirection = -Rotation.Vector();

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());

	return GetWorld()->LineTraceSingleByChannel(Hit, Location, EndPoint, ECollisionChannel::ECC_GameTraceChannel1, Params);
}

AController* AGuns::GetOwnerController() const
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if(OwnerPawn == nullptr)
	{
		return nullptr;
	}

	return OwnerPawn->GetController();
}

