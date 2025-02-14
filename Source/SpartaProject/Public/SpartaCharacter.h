#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SpartaCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
<<<<<<< HEAD
class UWidgetComponent;
=======
>>>>>>> d49eea0 (Fixed .gitignore to properly exclude unnecessary files)
struct FInputActionValue;

UCLASS()
class SPARTAPROJECT_API ASpartaCharacter : public ACharacter
{
	GENERATED_BODY()
<<<<<<< HEAD
	
public:
	ASpartaCharacter();


=======

public:
	ASpartaCharacter();

>>>>>>> d49eea0 (Fixed .gitignore to properly exclude unnecessary files)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	USpringArmComponent* SpringArmComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* CameraComp;
<<<<<<< HEAD
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	UWidgetComponent* OverheadWidget;

	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHelath() const;
	UFUNCTION(BlueprintCallable, Category = "Health")
	void AddHealth(float Amount);

protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float MaxHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float Health;

	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual float TakeDamage(
		float DamageAmount,
		struct FDamageEvent const& DamageEvent,
		AController* EventInstigator, 
		AActor* DamageCauser
	) override;
=======

protected:
	

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
>>>>>>> d49eea0 (Fixed .gitignore to properly exclude unnecessary files)

	UFUNCTION()
	void Move(const FInputActionValue& value);
	UFUNCTION()
	void StartJump(const FInputActionValue& value);
	UFUNCTION()
	void StopJump(const FInputActionValue& value);
	UFUNCTION()
	void Look(const FInputActionValue& value);
	UFUNCTION()
	void StartSprint(const FInputActionValue& value);
	UFUNCTION()
	void StopSprint(const FInputActionValue& value);
<<<<<<< HEAD
	UFUNCTION()
	void Menu(const FInputActionValue& value);

	void OnDeath();
	void UpdateOverheadHP();
=======

>>>>>>> d49eea0 (Fixed .gitignore to properly exclude unnecessary files)
private:
	float NormalSpeed;
	float SprintSpeedMultiplier;
	float SprintSpeed;
	int JumpCount;
};
