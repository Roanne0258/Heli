#include "SpartaMyGameMode.h"
#include "SpartaCharacter.h"
#include "SpartaMyPlayerController.h"
<<<<<<< HEAD
#include "SpartaGameState.h"
=======
>>>>>>> d49eea0 (Fixed .gitignore to properly exclude unnecessary files)

ASpartaMyGameMode::ASpartaMyGameMode()
{
	DefaultPawnClass = ASpartaCharacter::StaticClass();
	PlayerControllerClass = ASpartaMyPlayerController::StaticClass();
<<<<<<< HEAD
	GameStateClass = ASpartaGameState::StaticClass();
=======
>>>>>>> d49eea0 (Fixed .gitignore to properly exclude unnecessary files)
}

