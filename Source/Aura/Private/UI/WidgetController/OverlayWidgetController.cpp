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

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	// AttributeSet을 Aura 전용 AttributeSet으로 캐스팅 (실패 시 크래시)
	const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);

	// Health Attribute 값이 변경될 때 호출되는 델리게이트를 가져옴
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AuraAttributeSet->GetHealthAttribute())
		// Health 값이 변경되면 HealthChanged 함수를 실행하도록 등록
		.AddUObject(this, &UOverlayWidgetController::HealthChanged);

	// MaxHealth Attribute 값이 변경될 때 호출되는 델리게이트를 가져옴
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AuraAttributeSet->GetMaxHealthAttribute())
		// MaxHealth 값이 변경되면 HealthChanged 함수를 실행하도록 등록
		.AddUObject(this, &UOverlayWidgetController::MaxHealthChanged);
}

void UOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data) const
{
	// Data 내부에선 보통 Attribute 변경된 내용이 들어있으므로 New/OldValue 의 값이 있다.
	OnHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxHealthChanged.Broadcast(Data.NewValue);
}
