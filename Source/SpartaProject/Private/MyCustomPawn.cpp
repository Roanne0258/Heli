#include "MyCustomPawn.h"
#include "EnhancedInputComponent.h"
#include "CustomPlayerController.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/ArrowComponent.h"

AMyCustomPawn::AMyCustomPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	SetRootComponent(CollisionComp);

	CollisionComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CollisionComp->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);
	CollisionComp->SetCollisionResponseToAllChannels(ECR_Block);
	CollisionComp->SetSimulatePhysics(true); // 물리
	CollisionComp->SetEnableGravity(true); // 중력
	CollisionComp->SetLinearDamping(2.0f); // 공기 저항
	CollisionComp->SetAngularDamping(2.0f); // 회전 저항

	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	MeshComp->SetupAttachment(RootComponent);

	ArrowComp = CreateDefaultSubobject< UArrowComponent>(TEXT("Arrow"));
	ArrowComp->SetupAttachment(RootComponent);

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);

	VerticalSpeed = 0.0f;		// 상승/하강 속도
	Acceleration = 50.0f;       // 가속도 (초당 증가량)
	MaxVerticalSpeed = 300.0f;  // 최대 상승/하강 속도
	Deceleration = 30.0f;       // 감속도
	TurnSpeed = 50.0f;			// 회전속도
	LookSpeed = 50.0f;			// 기울기속도
	MaxSpeed = 500.0f;			// 최대속도
	SpeedMultiplier = 5.0f;		// 속도
}
void AMyCustomPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (ACustomPlayerController* PlayerController = Cast<ACustomPlayerController>(GetController()))
		{
			if (PlayerController->HeliUpDownAction)
			{
				EnhancedInput->BindAction(
					PlayerController->HeliUpDownAction,
					ETriggerEvent::Triggered,
					this,
					&AMyCustomPawn::HeliUpDown
				);
			}

			if (PlayerController->HeliRotateAction)
			{
				EnhancedInput->BindAction(
					PlayerController->HeliRotateAction,
					ETriggerEvent::Triggered,
					this,
					&AMyCustomPawn::HeliRotate
				);
			}

			if (PlayerController->HeliTiltAction)
			{
				EnhancedInput->BindAction(
					PlayerController->HeliTiltAction,
					ETriggerEvent::Triggered,
					this,
					&AMyCustomPawn::HeliTilt
				);
			}
		}
	}
}
void AMyCustomPawn::HeliUpDown(const FInputActionValue& value)
{
	if (!Controller) return;

	const float UpDownValue = value.Get<float>();

	if (!FMath::IsNearlyZero(UpDownValue))
	{
		if (UpDownValue < 0 && VerticalSpeed > 0)
		{
			VerticalSpeed = 0.0f;  // 상승 속도 제거
		}

		// 상승/하강 가속도 적용
		VerticalSpeed += UpDownValue * Acceleration * GetWorld()->DeltaTimeSeconds;
		VerticalSpeed = FMath::Clamp(VerticalSpeed, -MaxVerticalSpeed, MaxVerticalSpeed);

	}
	else
	{
			VerticalSpeed = FMath::FInterpTo(VerticalSpeed, 0.0f, GetWorld()->DeltaTimeSeconds, Deceleration);
	}

	// 최종 Z축 이동 적용
	AddActorLocalOffset(FVector(0, 0, VerticalSpeed * GetWorld()->DeltaTimeSeconds), true);
}
void AMyCustomPawn::HeliRotate(const FInputActionValue& value)
{
	if (!Controller) return;

	const float TurnInput = value.Get<float>();

	// 현재 회전 값 가져오기
	FRotator CurrentRotation = GetActorRotation();

	// Yaw(좌우 회전) 변경
	CurrentRotation.Yaw += TurnInput * TurnSpeed * GetWorld()->DeltaTimeSeconds;

	// 새로운 회전값 설정
	SetActorRotation(CurrentRotation);
}
void AMyCustomPawn::HeliTilt(const FInputActionValue& Value)
{
	if (!Controller) return;

	FVector2D LookInput = Value.Get<FVector2D>();

	// 현재 회전 값 가져오기
	FRotator CurrentRotation = GetActorRotation();

	// Pitch 변경 (Z축 이동 방지)
	float NewPitch = CurrentRotation.Pitch + LookInput.Y * LookSpeed * GetWorld()->DeltaTimeSeconds;

	// Pitch 값 제한
	NewPitch = FMath::Clamp(NewPitch, -80.0f, 80.0f);

	// Roll 변경 (Yaw는 A/D 키로 처리)
	float NewRoll = CurrentRotation.Roll + LookInput.X * LookSpeed * GetWorld()->DeltaTimeSeconds;
	NewRoll = FMath::Clamp(NewRoll, -80.0f, 80.0f);

	// 새로운 회전값 적용 (Z축 영향 없음)
	SetActorRotation(FRotator(NewPitch, CurrentRotation.Yaw, NewRoll));
}
void AMyCustomPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 현재 헬기의 회전 값 가져오기
	FRotator CurrentRotation = GetActorRotation();

	// Pitch & Roll 값 가져오기
	float Pitch = CurrentRotation.Pitch;
	float Roll = CurrentRotation.Roll;

	// Pitch와 Roll 값에 따른 이동 속도 계산
	float ForwardSpeed = FMath::Clamp(FMath::Abs(Pitch) * SpeedMultiplier, 0.0f, MaxSpeed);
	float SideSpeed = FMath::Clamp(FMath::Abs(Roll) * SpeedMultiplier, 0.0f, MaxSpeed);

	// 헬기의 Forward Vector 및 Right Vector 가져오기
	FVector ForwardDirection = GetActorForwardVector();
	FVector RightDirection = GetActorRightVector();

	// Z축 이동 제한 (수평 이동만 허용)
	ForwardDirection.Z = 0.0f;
	RightDirection.Z = 0.0f;
	ForwardDirection.Normalize();
	RightDirection.Normalize();

	FVector MoveDirection = FVector::ZeroVector;

	// Pitch에 따른 전진/후진
	if (Pitch > 0.0f)
	{
		MoveDirection -= ForwardDirection * ForwardSpeed;
	}
	else if (Pitch < 0.0f)
	{
		MoveDirection += ForwardDirection * ForwardSpeed;
	}

	// Roll에 따른 좌우 이동
	if (Roll > 0.0f)
	{
		MoveDirection += RightDirection * SideSpeed;
	}
	else if (Roll < 0.0f)
	{
		MoveDirection -= RightDirection * SideSpeed;
	}
	// 최종 이동 적용
	AddActorLocalOffset(MoveDirection * DeltaTime, true);
}
