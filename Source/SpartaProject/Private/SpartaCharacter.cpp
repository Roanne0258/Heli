#include "SpartaCharacter.h"
#include "SpartaMyPlayerController.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
<<<<<<< HEAD
#include "GameFramework/Actor.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"
#include "SpartaGameState.h"
=======
>>>>>>> d49eea0 (Fixed .gitignore to properly exclude unnecessary files)

ASpartaCharacter::ASpartaCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->TargetArmLength = 300.0f;
	SpringArmComp->bUsePawnControlRotation = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);
	CameraComp->bUsePawnControlRotation = false;

<<<<<<< HEAD
	OverheadWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("OverheadWidget"));
	OverheadWidget->SetupAttachment(GetMesh());
	OverheadWidget->SetWidgetSpace(EWidgetSpace::Screen);

=======
>>>>>>> d49eea0 (Fixed .gitignore to properly exclude unnecessary files)
	NormalSpeed = 600.0f;
	SprintSpeedMultiplier = 1.7f;
	SprintSpeed = NormalSpeed * SprintSpeedMultiplier;
	JumpCount = 0;

	GetCharacterMovement()->MaxWalkSpeed = NormalSpeed;
<<<<<<< HEAD

	MaxHealth = 100.0f;
	Health = MaxHealth;
}
void ASpartaCharacter::BeginPlay()
{
	Super::BeginPlay();
	UpdateOverheadHP();
=======
>>>>>>> d49eea0 (Fixed .gitignore to properly exclude unnecessary files)
}

void ASpartaCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (ASpartaMyPlayerController* PlayerController = Cast<ASpartaMyPlayerController>(GetController()))
		{
			if (PlayerController->MoveAction)
			{
				EnhancedInput->BindAction(
					PlayerController->MoveAction,
					ETriggerEvent::Triggered,
					this,
					&ASpartaCharacter::Move

				);
			}

			if (PlayerController->JumpAction)
			{
				EnhancedInput->BindAction(
					PlayerController->JumpAction,
					ETriggerEvent::Triggered,
					this,
					&ASpartaCharacter::StartJump

				);
			}

			if (PlayerController->JumpAction)
			{
				EnhancedInput->BindAction(
					PlayerController->JumpAction,
					ETriggerEvent::Completed,
					this,
					&ASpartaCharacter::StopJump

				);
			}

			if (PlayerController->LookAction)
			{
				EnhancedInput->BindAction(
					PlayerController->LookAction,
					ETriggerEvent::Triggered,
					this,
					&ASpartaCharacter::Look

				);
			}

			if (PlayerController->SprintAction)
			{
				EnhancedInput->BindAction(
					PlayerController->SprintAction,
					ETriggerEvent::Triggered,
					this,
					&ASpartaCharacter::StartSprint

				);
			}

			if (PlayerController->SprintAction)
			{
				EnhancedInput->BindAction(
					PlayerController->SprintAction,
					ETriggerEvent::Completed,
					this,
					&ASpartaCharacter::StopSprint

				);
			}
<<<<<<< HEAD
			if (PlayerController->MenuAction)
			{
				EnhancedInput->BindAction(
					PlayerController->MenuAction,
					ETriggerEvent::Completed,
					this,
					&ASpartaCharacter::Menu
				);
			}
=======
>>>>>>> d49eea0 (Fixed .gitignore to properly exclude unnecessary files)
		}
	}
}

void ASpartaCharacter::Move(const FInputActionValue& value)
{
<<<<<<< HEAD

=======
>>>>>>> d49eea0 (Fixed .gitignore to properly exclude unnecessary files)
	if (!Controller) return;

	const FVector2D MoveInput = value.Get<FVector2D>();

	if (!FMath::IsNearlyZero(MoveInput.X))
	{
		AddMovementInput(GetActorForwardVector(), MoveInput.X);
	}

	if (!FMath::IsNearlyZero(MoveInput.Y))
	{
		AddMovementInput(GetActorRightVector(), MoveInput.Y);
	}
}
void ASpartaCharacter::StartJump(const FInputActionValue& value)
{
	if (value.Get<bool>())
	{
		Jump();
<<<<<<< HEAD
=======
		JumpCount++;
		UE_LOG(LogTemp, Warning, TEXT("JumpCount : %d"), JumpCount);
>>>>>>> d49eea0 (Fixed .gitignore to properly exclude unnecessary files)
	}
}
void ASpartaCharacter::StopJump(const FInputActionValue& value)
{
	if (!value.Get<bool>())
	{
		StopJumping();
<<<<<<< HEAD
		JumpCount++;
		//UE_LOG(LogTemp, Warning, TEXT("JumpCount : %d"), JumpCount);
=======
>>>>>>> d49eea0 (Fixed .gitignore to properly exclude unnecessary files)
	}
}
void ASpartaCharacter::Look(const FInputActionValue& value)
{
	FVector2D LookInput = value.Get<FVector2D>();

	AddControllerYawInput(LookInput.X);
	AddControllerPitchInput(LookInput.Y);
}
void ASpartaCharacter::StartSprint(const FInputActionValue& value)
{
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
	}
}
void ASpartaCharacter::StopSprint(const FInputActionValue& value)
{
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->MaxWalkSpeed = NormalSpeed;
	}
<<<<<<< HEAD
}
void ASpartaCharacter::Menu(const FInputActionValue& Value)
{
	const bool bPressed = Value.Get<bool>();
	FString CurrentMapName = GetWorld()->GetMapName();

	ASpartaMyPlayerController* PlayerController = Cast<ASpartaMyPlayerController>(GetController());

	if (PlayerController)
	{

		if (CurrentMapName.Contains("MenuLevel"))
		{
			PlayerController->ShowMainMenu(false);
		}
		else
		{
			if (PlayerController->GetHUDWidget() && PlayerController->GetHUDWidget()->IsInViewport())
			{
				PlayerController->ShowMainMenu(true);
			}
			else
			{
				PlayerController->ShowGameHUD();
			}
		}
	}
}


float ASpartaCharacter::GetHelath() const
{
	return Health;
}
// 체력 회복 함수
void ASpartaCharacter::AddHealth(float Amount)
{
	// 체력을 회복시킴. 최대 체력을 초과하지 않도록 제한함
	Health = FMath::Clamp(Health + Amount, 0.0f, MaxHealth);
	UpdateOverheadHP();
}
// 데미지 처리 함수
float ASpartaCharacter::TakeDamage(
	float DamageAmount,
	const FDamageEvent& DamageEvent,
	AController* EventInstigator,
	AActor* DamageCauser
)
{
	// 기본 데미지 처리 로직 호출 (필수는 아님)
	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	// 체력을 데미지만큼 감소시키고, 0 이하로 떨어지지 않도록 Clamp
	Health = FMath::Clamp(Health - DamageAmount, 0.0f, MaxHealth);
	UpdateOverheadHP();

	// 체력이 0 이하가 되면 사망 처리
	if (Health <= 0.0f)
	{
		OnDeath();
	}

	// 실제 적용된 데미지를 반환
	return ActualDamage;
}
// 사망 처리 함수
void ASpartaCharacter::OnDeath()
{
	// 사망 후 로직
	ASpartaGameState* SpartaGameState = GetWorld() ? GetWorld()->GetGameState<ASpartaGameState>() : nullptr;
	if (SpartaGameState)
	{
		SpartaGameState->OnGameOver();
	}
}

void ASpartaCharacter::UpdateOverheadHP()
{
	if (!OverheadWidget) return;

	UUserWidget* OverheadWidgetInstance = OverheadWidget->GetUserWidgetObject();
	if (!OverheadWidgetInstance) return;

	if (UTextBlock* HPText = Cast<UTextBlock>(OverheadWidgetInstance->GetWidgetFromName(TEXT("OverHeadHP"))))
	{
		HPText->SetText(FText::FromString(FString::Printf(TEXT("%.0f / %.0f"), Health, MaxHealth)));
	}
=======
>>>>>>> d49eea0 (Fixed .gitignore to properly exclude unnecessary files)
}