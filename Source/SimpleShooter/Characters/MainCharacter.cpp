// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include "SimpleShooter/Guns/Guns.h"
#include "Components/CapsuleComponent.h"
#include "SimpleShooter/SimpleShooterGameModeBase.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	Gun = GetWorld()->SpawnActor<AGuns>(GunClass);

	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);
	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	Gun->SetOwner(this);

	Health = MaxHealth;
}

bool AMainCharacter::IsDead() const
{
	return Health <=0;
}

float AMainCharacter::HealthPercent() const
{
	return Health / MaxHealth;
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(IsRecoilling)
	{
	float FinalRecoilPitch = Gun->Recoil * FMath::FRandRange(-1.f, -1.2f);
	float FinalRecoilYaw = Gun->Recoil * FMath::FRandRange(3.f, -3.f);
	AddControllerPitchInput(FinalRecoilPitch);
	AddControllerYawInput(FinalRecoilYaw);
	}
}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AMainCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveSide"), this, &AMainCharacter::MoveSide);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("LookSide"), this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis(TEXT("ContLookUp"), this, &AMainCharacter::ContLookUp);
	PlayerInputComponent->BindAxis(TEXT("ContLookSide"), this, &AMainCharacter::ContLookSide);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("ShootGun"), EInputEvent::IE_Pressed, this, &AMainCharacter::StartFire);
	PlayerInputComponent->BindAction(TEXT("ShootGun"), EInputEvent::IE_Released, this, &AMainCharacter::ResetFire);
	PlayerInputComponent->BindAction(TEXT("Reload"), EInputEvent::IE_Pressed, this, &AMainCharacter::Reload);
}

float AMainCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const &DamageEvent, class AController *EventInstigator, AActor *DamageCauser) 
{
	float DamageApplied = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	DamageApplied = FMath::Min(Health, DamageApplied);
	Health -= DamageApplied;
	UE_LOG(LogTemp, Warning, TEXT("Remaining Health %f"), Health);

	if (IsDead())
	{
		ASimpleShooterGameModeBase* GameMode = GetWorld()->GetAuthGameMode<ASimpleShooterGameModeBase>();

		if (GameMode != nullptr)
		{
			GameMode->PawnKilled(this);
		}
		
		DetachFromControllerPendingDestroy();

		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);	
	}
	
	return DamageApplied;
}

void AMainCharacter::MoveForward(float AxisValue) 
{
	AddMovementInput(GetActorForwardVector()* AxisValue);
}

void AMainCharacter::MoveSide(float AxisValue) 
{
	AddMovementInput(GetActorRightVector()* AxisValue);
}

void AMainCharacter::ContLookUp(float AxisValue) 
{
	AddControllerPitchInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void AMainCharacter::ContLookSide(float AxisValue) 
{
	AddControllerYawInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void AMainCharacter::Shoot() 
{
	if (Ammo <= 0){return;}
	Ammo = Ammo - 1;
	Gun->PullTrigger();	

	GetWorld()->GetTimerManager().SetTimer(RecoilTimer, this, &AMainCharacter::StopRecoil, 0.1f, true);
	IsRecoilling = true;
}

void AMainCharacter::Reload() 
{
	if (MaxAmmo <= 0 || Ammo >= 30){return;}
	
	if(MaxAmmo < (30 - Ammo))
	{
		Ammo = Ammo + MaxAmmo;
		MaxAmmo = 0;
	}else
	{
		MaxAmmo = MaxAmmo - (30 - Ammo);
		Ammo = 30;
	}
}

void AMainCharacter::StartFire() 
{
	Shoot();

	GetWorld()->GetTimerManager().SetTimer(Timer, this, &AMainCharacter::Shoot, Gun->FireDelay, true);
}

void AMainCharacter::ResetFire() 
{
	GetWorld()->GetTimerManager().ClearTimer(Timer);
}

void AMainCharacter::StopRecoil() 
{
	IsRecoilling = false;

	GetWorld()->GetTimerManager().ClearTimer(RecoilTimer);
}

int AMainCharacter::Ammunitions()
{
	return Ammo;
}

int AMainCharacter::MaxAmmu() 
{
	return MaxAmmo;
}






