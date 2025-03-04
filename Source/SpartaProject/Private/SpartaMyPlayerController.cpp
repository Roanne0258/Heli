#include "SpartaMyPlayerController.h"
<<<<<<< HEAD
#include "SpartaGameState.h"
#include "SpartaGameInstance.h"
#include "EnhancedInputSubsystems.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"

ASpartaMyPlayerController::ASpartaMyPlayerController()
	: InputMappingContext(nullptr),
	MoveAction(nullptr),
	JumpAction(nullptr),
	LookAction(nullptr),
	SprintAction(nullptr),
	MenuAction(nullptr),
	HUDWidgetClass(nullptr),
	HUDWidgetInstance(nullptr),
	MainMenuWidgetClass(nullptr),
	MainMenuWidgetInstance(nullptr)
{
=======
#include "EnhancedInputSubsystems.h"

ASpartaMyPlayerController::ASpartaMyPlayerController()
	:	InputMappingContext(nullptr),
		MoveAction(nullptr),
		SprintAction(nullptr),
		JumpAction(nullptr),
		LookAction(nullptr)

{

>>>>>>> d49eea0 (Fixed .gitignore to properly exclude unnecessary files)
}

void ASpartaMyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
<<<<<<< HEAD
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
			LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
=======
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
>>>>>>> d49eea0 (Fixed .gitignore to properly exclude unnecessary files)
		{
			if (InputMappingContext)
			{
				Subsystem->AddMappingContext(InputMappingContext, 0);
			}
		}
	}
<<<<<<< HEAD

	// 게임 실행 시 메뉴 레벨에서 메뉴 UI 먼저 표시
	FString CurrentMapName = GetWorld()->GetMapName();
	if (CurrentMapName.Contains("MenuLevel"))
	{
		ShowMainMenu(false);
	}
}

UUserWidget* ASpartaMyPlayerController::GetHUDWidget() const
{
	return HUDWidgetInstance;
}

// 메뉴 UI 표시
void ASpartaMyPlayerController::ShowMainMenu(bool bIsRestart)
{
	// HUD가 켜져 있다면 닫기
	if (HUDWidgetInstance)
	{
		HUDWidgetInstance->RemoveFromParent();
		HUDWidgetInstance = nullptr;
	}

	// 이미 메뉴가 떠 있으면 제거
	if (MainMenuWidgetInstance)
	{
		MainMenuWidgetInstance->RemoveFromParent();
		MainMenuWidgetInstance = nullptr;
	}

	// 메뉴 UI 생성
	if (MainMenuWidgetClass)
	{
		MainMenuWidgetInstance = CreateWidget<UUserWidget>(this, MainMenuWidgetClass);
		if (MainMenuWidgetInstance)
		{
			MainMenuWidgetInstance->AddToViewport();

			bShowMouseCursor = true;
			SetInputMode(FInputModeUIOnly());
		}

		if (UTextBlock* ButtonText = Cast<UTextBlock>(MainMenuWidgetInstance->GetWidgetFromName(TEXT("StartButtonText"))))
		{
			if (bIsRestart)
			{
				ButtonText->SetText(FText::FromString(TEXT("Restart")));
				
			}
			else
			{
				ButtonText->SetText(FText::FromString(TEXT("Start")));
			}
		}
		
		if (bIsRestart)
		{
			UFunction* PlayAnimFunc = MainMenuWidgetInstance->FindFunction(FName("PlayGameOverAnim"));
			if (PlayAnimFunc)
			{
				MainMenuWidgetInstance->ProcessEvent(PlayAnimFunc, nullptr);
			}

			if (UTextBlock* TotalScoreText = Cast<UTextBlock>(MainMenuWidgetInstance->GetWidgetFromName("TotalScoreText")))
			{
				if (USpartaGameInstance* SpartaGameInstance = Cast<USpartaGameInstance>(UGameplayStatics::GetGameInstance(this)))
				{
					TotalScoreText->SetText(FText::FromString(
						FString::Printf(TEXT("Total Score: %d"), SpartaGameInstance->TotalScore)
					));
				}
			}
		}
	}
}

// 게임 HUD 표시
void ASpartaMyPlayerController::ShowGameHUD()
{
	// HUD가 켜져 있다면 닫기
	if (HUDWidgetInstance)
	{
		HUDWidgetInstance->RemoveFromParent();
		HUDWidgetInstance = nullptr;
	}

	// 이미 메뉴가 떠 있으면 제거
	if (MainMenuWidgetInstance)
	{
		MainMenuWidgetInstance->RemoveFromParent();
		MainMenuWidgetInstance = nullptr;
	}

	if (HUDWidgetClass)
	{
		HUDWidgetInstance = CreateWidget<UUserWidget>(this, HUDWidgetClass);
		if (HUDWidgetInstance)
		{
			HUDWidgetInstance->AddToViewport();

			bShowMouseCursor = false;
			SetInputMode(FInputModeGameOnly());

			ASpartaGameState* SpartaGameState = GetWorld() ? GetWorld()->GetGameState<ASpartaGameState>() : nullptr;
			if (SpartaGameState)
			{
				SpartaGameState->UpdateHUD();
			}
		}
	}
}

// 게임 시작 - BasicLevel 오픈, GameInstance 데이터 리셋
void ASpartaMyPlayerController::StartGame()
{
	if (USpartaGameInstance* SpartaGameInstance = Cast<USpartaGameInstance>(UGameplayStatics::GetGameInstance(this)))
	{
		SpartaGameInstance->CurrentLevelIndex = 0;
		SpartaGameInstance->TotalScore = 0;
	}

	UGameplayStatics::OpenLevel(GetWorld(), FName("BasicLevel"));
	SetPause(false);
=======
>>>>>>> d49eea0 (Fixed .gitignore to properly exclude unnecessary files)
}