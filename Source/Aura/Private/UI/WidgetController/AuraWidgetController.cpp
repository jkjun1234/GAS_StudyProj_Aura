#include "UI/WidgetController/AuraWidgetController.h"

// 위젯컨트롤러 설정 파라미터(PS,PC,ASC,AttributeSet)을 입력받음
void UAuraWidgetController::SetWidgetControllerParams(FWidgetControllerParams WCParams)
{
	PlayerController = WCParams.PlayerController;
	PlayerState = WCParams.PlayerState;
	AbilitySystemComponent = WCParams.AbilitySystemComponent;
	AttributeSet = WCParams.AttributeSet;
}
