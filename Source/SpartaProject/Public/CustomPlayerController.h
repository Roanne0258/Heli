#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CustomPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class SPARTAPROJECT_API ACustomPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ACustomPlayerController();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputMappingContext* InputMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* HeliUpDownAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* HeliRotateAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* HeliTiltAction;

protected:
	virtual void BeginPlay() override;
};
