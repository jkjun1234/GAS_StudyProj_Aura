// AuraHUD.cpp

#include "UI/HUD/AuraHUD.h"

#include "UI/Widget/AuraUserWidget.h"
#include "UI/WidgetController/OverlayWidgetController.h"

UOverlayWidgetController* AAuraHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	if (OverlayWidgetController == nullptr)
	{
		// 위젯 컨트롤러가 널포인터일시 OverlayWIdgetControllerClass를 갖는 새 오브젝트를 만들어 할당해준다.
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WCParams);

		return OverlayWidgetController;	// Set하여 오버레이 위젯컨트롤러를 반환
	}
	
	return OverlayWidgetController;
}

// Overlay 위젯 초기화하는 곳
// AuraCharacter.cpp 에서 InitAbilityActorInfo() 에서 실행함
void AAuraHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	// checkf 를 통해 해당 값이 Null 인경우 TEXT를 출력하며 중단
	checkf(OverlayWidgetClass, TEXT("Overlay WidgetClass 초기화 되지 않음 BP_AuraHUD 에서 WIdgetClass 를 설정필요"))
	checkf(OverlayWidgetControllerClass, TEXT("Overlay Widget Controller 초기화 필요 BP_AuraHUD를 확인"));
	
	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget = Cast<UAuraUserWidget>(Widget);

	// WidgetControllerParams 생성자를 통한 파라미터 초기화
	const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
	// 위젯 파라미터를 던져준 후 위젯 컨트롤러를 
	UOverlayWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams);

	OverlayWidget->SetWidgetController(WidgetController);
	WidgetController->BroadcastInitialValues();	// 위젯컨트롤러 설정후 초기값 브로드캐스트
	Widget->AddToViewport();
}
