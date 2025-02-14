#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

UCLASS()
class SPARTAPROJECT_API AItem : public AActor
{
	GENERATED_BODY()

public:
	AItem();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Components")
	USceneComponent* SceneRoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Components")
	UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Properties")
	float RotationSpeed;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(CallInEditor, Category = "Item|Transform")
	void ResetActorPosition();

	UFUNCTION(BlueprintPure, Category = "Item|Properties")
	float GetRotationSpeed() const;

};