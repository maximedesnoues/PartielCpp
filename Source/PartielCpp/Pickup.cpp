// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickup.h"
#include "PartielCppCharacter.h"
#include "Components/SphereComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

// Sets default values
APickup::APickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CoinMesh"));
	RootComponent = mesh;

	collider = CreateDefaultSubobject<USphereComponent>(TEXT("collider"));
	collider->InitSphereRadius(100.f);
	collider->OnComponentBeginOverlap.AddDynamic(this, &APickup::OnOverlapBegin);

	collider->SetupAttachment(mesh);

}

void APickup::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (PickupSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, PickupSound, GetActorLocation());
		GEngine->AddOnScreenDebugMessage(3, 5.0f, FColor::Red, FString::Printf(TEXT("SON PIECE !")));
	}

	Destroy();

	APartielCppCharacter* player = Cast<APartielCppCharacter>(UGameplayStatics::GetActorOfClass(GetWorld(), APartielCppCharacter::StaticClass()));
	player->IncreaseScore();
}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator rotation = GetActorRotation();
	rotation.Yaw += 10;
	SetActorRotation(rotation);

}

