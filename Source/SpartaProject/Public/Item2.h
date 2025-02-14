// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item2.generated.h"

UCLASS()
class SPARTAPROJECT_API AItem2 : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem2();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MovingItem|Components")
	USceneComponent* SceneRoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MovingItem|Components")
	UStaticMeshComponent* StaticMeshComp;

	// 이동 속도
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MovingItem|Movement")
	float MoveSpeed;

	// 이동 범위 (왕복 거리)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MovingItem|Movement")
	float MaxRange;

	// 시작 위치 저장
	FVector StartLocation;

	// 이동 방향 (1: 정방향, -1: 반대방향)
	int Direction;

};