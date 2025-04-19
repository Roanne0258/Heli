# Unreal Engine 5 - Custom Pawn Movement System

## 📌 프로젝트 개요
이 프로젝트는 `Pawn` 클래스를 활용하여 **CharacterMovementComponent 없이 직접 이동을 구현하는 예제**입니다.

## 🚀 주요 기능
- **Pawn 기반 이동 구현 (CharacterMovementComponent 사용 X)**
- **W/S 키로 상승 및 하강 구현 **
- **A/D 키로 회전, 마우스로 기울기 조작 (Tilt)**
- **Enhanced Input을 활용한 입력 처리**
- **중력 효과 없이 직접 속도를 조절하여 이동**

## 📂 프로젝트 구조
```
📁 Source
 ┣ 📂 Private,Public
 ┃ ┣ 📜 MyCustomPawn.cpp/h
 ┃ ┣ 📜 MyGameMode.cpp/h
 ┃ ┗ 📜 CustomPlayerController.cpp/h
```

🔧 실행 세팅 방법

1. 프로젝트 설정 변경

(1) Project Settings에서 설정하는 방법

Edit → Project Settings 열기

Maps & Modes → Default Modes 이동

GameMode Override에 BP_MyGameMode 설정

Default Pawn Class를 BP_CustomPawn으로 설정

Player Controller Class를 BP_CustomPlayerController로 설정

(2) World Settings에서 설정하는 방법

Window → World Settings 열기

GameMode Override에 BP_MyGameMode 설정

Default Pawn Class를 BP_CustomPawn으로 설정

Player Controller Class를 BP_CustomPlayerController로 설정

(3) Possess 설정 (필수)

BP_CustomPlayerController에서 Auto Possess Player를 Player 0으로 설정

## 📜 주요 코드
### **1. Pawn 기본 설정**
```cpp
AMyCustomPawn::AMyCustomPawn()
{
    PrimaryActorTick.bCanEverTick = true;

    CollisionComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
    SetRootComponent(CollisionComp);
    
    CollisionComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    CollisionComp->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);
    CollisionComp->SetCollisionResponseToAllChannels(ECR_Block);
    CollisionComp->SetSimulatePhysics(false); // 중력 효과 없음
}
```

### **2. Enhanced Input 설정 및 바인딩**
```cpp
void AMyCustomPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    
    if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        if (ACustomPlayerController* PlayerController = Cast<ACustomPlayerController>(GetController()))
        {
            EnhancedInput->BindAction(PlayerController->HeliUpDownAction, ETriggerEvent::Triggered, this, &AMyCustomPawn::HeliUpDown);
            EnhancedInput->BindAction(PlayerController->HeliRotateAction, ETriggerEvent::Triggered, this, &AMyCustomPawn::HeliRotate);
            EnhancedInput->BindAction(PlayerController->HeliTiltAction, ETriggerEvent::Triggered, this, &AMyCustomPawn::HeliTilt);
        }
    }
}
```

### **3. W/S 키로 상승 및 하강 (`HeliUpDown`)**
```cpp
void AMyCustomPawn::HeliUpDown(const FInputActionValue& value)
{
    if (!Controller) return;

    const float UpDownValue = value.Get<float>();
    
    if (!FMath::IsNearlyZero(UpDownValue))
    {
        VerticalSpeed += UpDownValue * Acceleration * GetWorld()->DeltaTimeSeconds;
        VerticalSpeed = FMath::Clamp(VerticalSpeed, -MaxVerticalSpeed, MaxVerticalSpeed);
    }
    else
    {
        VerticalSpeed = FMath::FInterpTo(VerticalSpeed, 0.0f, GetWorld()->DeltaTimeSeconds, Deceleration);
    }

    AddActorLocalOffset(FVector(0, 0, VerticalSpeed * GetWorld()->DeltaTimeSeconds), true);
}
```

### **4. A/D 키로 회전 (`HeliRotate`)**
```cpp
void AMyCustomPawn::HeliRotate(const FInputActionValue& value)
{
    if (!Controller) return;
    
    const float TurnInput = value.Get<float>();
    FRotator CurrentRotation = GetActorRotation();
    CurrentRotation.Yaw += TurnInput * TurnSpeed * GetWorld()->DeltaTimeSeconds;
    SetActorRotation(CurrentRotation);
}
```

### **5. 마우스로 기울기 조작 (`HeliTilt`)**
```cpp
void AMyCustomPawn::HeliTilt(const FInputActionValue& Value)
{
    if (!Controller) return;
    FVector2D LookInput = Value.Get<FVector2D>();
    FRotator CurrentRotation = GetActorRotation();

    float NewPitch = FMath::Clamp(CurrentRotation.Pitch + LookInput.Y * LookSpeed * GetWorld()->DeltaTimeSeconds, -80.0f, 80.0f);
    float NewRoll = FMath::Clamp(CurrentRotation.Roll + LookInput.X * LookSpeed * GetWorld()->DeltaTimeSeconds, -90.0f, 90.0f);

    SetActorRotation(FRotator(NewPitch, CurrentRotation.Yaw, NewRoll));
}
```

## 🛠️ 향후 추가 예정
- 중력 적용 및 자연스러운 낙하 구현
- 더 현실적인 헬기 조작감 추가
- 헬기 모델 적용

## 📜 라이선스
이 프로젝트는 자유롭게 수정 및 배포할 수 있습니다. 사용 시 출처를 남겨주세요! 🚀

