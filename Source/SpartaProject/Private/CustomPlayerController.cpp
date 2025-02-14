#include "CustomPlayerController.h"
#include "EnhancedInputSubsystems.h"

ACustomPlayerController::ACustomPlayerController()
	:	InputMappingContext(nullptr),
		HeliUpDownAction(nullptr),
		HeliRotateAction(nullptr),
		HeliTiltAction(nullptr)
{
	
}

void ACustomPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* SubSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (InputMappingContext)
			{
				SubSystem->AddMappingContext(InputMappingContext, 0);
			}
		}
	}
}