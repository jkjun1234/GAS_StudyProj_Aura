// AuraPlayerController.cpp

#include "Player/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();

	check(AuraInputContext);	// AuraInputContext 가 유효하지 않으면 실행 종료 및 에러 반환

	// Subsystem은 싱글톤으로 게임 내 1개만 존재
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);

	// IMC(입력 매핑컨텍스트를 에디터에서 가져와 InputSubsystem으로 설정
	Subsystem->AddMappingContext(AuraInputContext, 0);

	bShowMouseCursor = true;	// TopDown 방식 게임을 위해 마우스 커서 표시
	DefaultMouseCursor = EMouseCursor::Default;

	// 마우스 커서 설정
	FInputModeGameAndUI InputModeData;	// 입력모드를 제어하기 위한 데이터 
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);	// 뷰포트에 마우스가 갇히지 않도록 설정
	InputModeData.SetHideCursorDuringCapture(false);	// 게임 플레이 시작시 커서가 사라지지않도록 설정
	SetInputMode(InputModeData);	// 설정한 입력 모드를 적용
}

