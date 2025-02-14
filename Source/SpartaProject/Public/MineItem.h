#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "MineItem.generated.h"

UCLASS()
class SPARTAPROJECT_API AMineItem : public ABaseItem
{
    GENERATED_BODY()

public:
    AMineItem();

    USphereComponent* ExplosionCollision;
    // 폭발까지 걸리는 시간 (5초)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mine")
    float ExplosionDelay;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mine")
    float ExplosionRadius;
    // 폭발 데미지
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mine")
    int32 ExplosionDamage;

    FTimerHandle ExplosionTimerHandle;

    virtual void ActivateItem(AActor* Activator) override;

    void Explode();
};