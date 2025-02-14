#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyCustomPawn.generated.h"

class UCapsuleComponent;
class USkeletalMeshComponent;
class USpringArmComponent;
class UCameraComponent;
class UArrowComponent;
struct FInputActionValue;

UCLASS()
class SPARTAPROJECT_API AMyCustomPawn : public APawn
{
	GENERATED_BODY()

public:
	AMyCustomPawn();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	UCapsuleComponent* CollisionComp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	USkeletalMeshComponent* MeshComp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	USpringArmComponent* SpringArmComp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	UArrowComponent* ArrowComp;

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void HeliUpDown(const FInputActionValue& value);
	UFUNCTION()
	void HeliRotate(const FInputActionValue& value);
	UFUNCTION()
	void HeliTilt(const FInputActionValue& value);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flight Settings")
	float VerticalSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flight Settings")
	float Acceleration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flight Settings")
	float MaxVerticalSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flight Settings")
	float Deceleration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flight Settings")
	float TurnSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flight Settings")
	float LookSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flight Settings")
	float SpeedMultiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flight Settings")
	float MaxSpeed;

	virtual void Tick(float DeltaTime) override;
};
