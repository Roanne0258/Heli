#include "MyGameMode.h"
#include "MyCustomPawn.h"
#include "CustomPlayerController.h"

AMyGameMode::AMyGameMode()
{
	DefaultPawnClass = AMyCustomPawn::StaticClass();
	PlayerControllerClass = ACustomPlayerController::StaticClass();
}