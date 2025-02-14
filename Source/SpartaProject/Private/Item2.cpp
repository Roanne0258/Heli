#include "Item2.h"

AItem2::AItem2()
{
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneRoot);

	PrimaryActorTick.bCanEverTick = true;

	MoveSpeed = 100.0f;  // 기본 이동 속도
	MaxRange = 500.0f;   // 이동 범위
	Direction = 1;       // 초기 이동 방향

}

// Called when the game starts or when spawned
void AItem2::BeginPlay()
{
	Super::BeginPlay();

	// 시작 위치 저장
	StartLocation = GetActorLocation();
	
}

// Called every frame
void AItem2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// 이동 거리 계산
	FVector CurrentLocation = GetActorLocation();
	float DistanceMoved = (CurrentLocation - StartLocation).Size();

	// 최대 범위를 넘었으면 방향 변경
	if (DistanceMoved >= MaxRange)
	{
		Direction *= -1;
	}

	// 새 위치 계산 및 적용
	FVector NewLocation = CurrentLocation + FVector(MoveSpeed * DeltaTime * Direction, 0.0f, 0.0f);
	SetActorLocation(NewLocation);

}

