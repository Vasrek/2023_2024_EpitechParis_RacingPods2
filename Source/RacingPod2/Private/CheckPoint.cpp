#include "CheckPoint.h"
#include "Components/SphereComponent.h"
#include "Pawns/Bird.h"

// Sets default values
ACheckPoint::ACheckPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemStaticMesh"));
	RootComponent = ItemMesh;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCol"));
	Sphere->SetupAttachment(GetRootComponent());

}

// Called when the game starts or when spawned
void ACheckPoint::BeginPlay()
{
	Super::BeginPlay();

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ACheckPoint::OnSphereOverlap);
	
}

void ACheckPoint::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool FromSweep, const FHitResult& SweepResult)
{
	ABird* Bird = Cast<ABird>(OtherActor);
	if (Bird)
	{
		if (Bird->GetNbCheckPointPassed() < Bird->GetNbMaxCheckPoint())
		{
			Bird->EndGame();
		}
		else
		{
			Bird->SetNbCheckPointPassed(Bird->GetNbCheckPointPassed() + 1);
		}
	}
}

// Called every frame
void ACheckPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

