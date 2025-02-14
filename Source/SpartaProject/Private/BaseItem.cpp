#include "BaseItem.h"
#include "Components/SphereComponent.h"

ABaseItem::ABaseItem()
{
    PrimaryActorTick.bCanEverTick = false;

    // 루트 컴포넌트 생성 및 설정
    Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
    SetRootComponent(Scene);

    // 충돌 컴포넌트 생성 및 설정
    Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
    // 겹침만 감지하는 프로파일 설정
    Collision->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
    // 루트 컴포넌트로 설정
    Collision->SetupAttachment(Scene);

    // 스태틱 메시 컴포넌트 생성 및 설정
    StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
    StaticMesh->SetupAttachment(Collision);
    // 메시가 불필요하게 충돌을 막지 않도록 하기 위해, 별도로 NoCollision 등으로 설정할 수 있음.

     //Overlap 이벤트 바인딩 아주 중요한 개념
    Collision->OnComponentBeginOverlap.AddDynamic(this, &ABaseItem::OnItemOverlap);
    Collision->OnComponentEndOverlap.AddDynamic(this, &ABaseItem::OnItemEndOverlap);
}

// 플레이어가 아이템 범위에 들어왔을 때 동작
void ABaseItem::OnItemOverlap(UPrimitiveComponent* OverlappedComp,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex,
    bool bFromSweep,
    const FHitResult& SweepResult)
{
    if (OtherActor && OtherActor->ActorHasTag("Player"))
    {
        GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Overlap!!!")));
        ActivateItem(OtherActor);
    }
	// 기본은 빈 함수 - 각 자식 클래스에서 구현
}

// 플레이어가 아이템 범위를 벗어났을 때 동작
void ABaseItem::OnItemEndOverlap(UPrimitiveComponent* OverlappedComp,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex)
{
}

// 아이템이 사용(Activate)되었을 때 동작
void ABaseItem::ActivateItem(AActor* Activator)
{
	// 기본은 빈 함수 - 자식 클래스에서 구현
}

// 아이템 유형을 반환
FName ABaseItem::GetItemType() const
{
	return ItemType;
}

// 아이템을 파괴(제거)하는 함수
void ABaseItem::DestroyItem()
{
	// AActor에서 제공하는 Destroy() 함수로 객체 제거
	Destroy();
}