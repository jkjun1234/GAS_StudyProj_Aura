// AuraPlayerController.cpp

#include "Player/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include  "EnhancedInputComponent.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();

	check(AuraInputContext); // AuraInputContext 가 유효하지 않으면 실행 종료 및 에러 반환

	// Subsystem은 싱글톤으로 게임 내 1개만 존재
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
		GetLocalPlayer());
	check(Subsystem);

	// IMC(입력 매핑컨텍스트를 에디터에서 가져와 InputSubsystem으로 설정
	Subsystem->AddMappingContext(AuraInputContext, 0);

	bShowMouseCursor = true; // TopDown 방식 게임을 위해 마우스 커서 표시
	DefaultMouseCursor = EMouseCursor::Default;

	// 마우스 커서 설정
	FInputModeGameAndUI InputModeData; // 입력모드를 제어하기 위한 데이터 
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock); // 뷰포트에 마우스가 갇히지 않도록 설정
	InputModeData.SetHideCursorDuringCapture(false); // 게임 플레이 시작시 커서가 사라지지않도록 설정
	SetInputMode(InputModeData); // 설정한 입력 모드를 적용
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// CastChecked : 캐스팅이 정상적으로 되었는지 확인 실패시 프로그램 중단 후 에러 발생
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	// Move 입력 바인딩 ThisClass = AAuraPlayerController 와 동일
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::Move);
}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>(); // X, Y 2개의 축 값을 받기
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.0f); // Yaw 축값만 얻어오기 ( 캐릭터의 좌우 회전을 위한 회전축 )

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X); // X 축 (캐릭터의 앞방향을 얻어옴)
	const FVector RightDirection = FRotationMatrix(Rotation).GetUnitAxis(EAxis::Y); // Y 축 (캐릭터의 우측 방향을 얻어옴)

	// Pawn 이 존재한다면~
	if (APawn* ControllerPawn = GetPawn<APawn>())
	{
		// 2D 좌표로 볼때 X축은 A,D || Y축은 W,S 이다.
		//  W , S 키는 앞/뒤로 이동하는 것으로 2D 좌표로 볼때 Y 축이므로 캐릭터의 전방을 Y축으로 설정
		ControllerPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		// A, D 키는 좌/우로 이동하는 것으로 2D 좌표로 볼 때 X 축이므로 
		ControllerPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}
