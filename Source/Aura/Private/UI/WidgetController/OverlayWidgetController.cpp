// OverlayWidgetController.cpp

#include "UI/WidgetController/OverlayWidgetController.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	// (미션 1.) AttributeSet의 값을 읽어와 최대체력,체력 등 속성값을 초기화 후 전달

	// AttributeSet 얻어오기 값 변화를 막기위해 const 사용
	const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);

	// 체력 초기값 브로드캐스트(해당 델리게이트를 바인딩한 곳에 모두 전달)
	OnHealthChanged.Broadcast(AuraAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(AuraAttributeSet->GetMaxHealth());
}
