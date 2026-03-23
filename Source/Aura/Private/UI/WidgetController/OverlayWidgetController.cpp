// OverlayWidgetController.cpp

#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	// (미션 1.) AttributeSet의 값을 읽어와 최대체력,체력 등 속성값을 초기화 후 전달

	// AttributeSet 얻어오기 값 변화를 막기위해 const 사용
	const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);

	// 체력,마나 초기값 브로드캐스트(해당 델리게이트를 바인딩한 곳에 모두 전달)
	OnHealthChanged.Broadcast(AuraAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(AuraAttributeSet->GetMaxHealth());
	OnManaChanged.Broadcast(AuraAttributeSet->GetMana());
	OnMaxManaChanged.Broadcast(AuraAttributeSet->GetMaxMana());
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

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		                      AuraAttributeSet->GetManaAttribute())
	                      .AddUObject(this, &UOverlayWidgetController::ManaChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		                      AuraAttributeSet->GetMaxManaAttribute())
	                      .AddUObject(this, &UOverlayWidgetController::MaxManaChanged);

	// ASC 에서 AssetTags를 담는 TagContainer를 브로드 캐스팅하여 해당 람다 함수를 바인딩함
	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->EffectAssetTags.AddLambda(
		[this](const FGameplayTagContainer& AssetTags)
		{
			for (const FGameplayTag& Tag : AssetTags)
			{
				const FString Msg = FString::Printf(TEXT("GE Tag: %s"), *Tag.ToString());
				// 키 값으로 -1을 주는 경우 최신 메세지가 지난 메세지를 가리지않음 
				GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Blue, Msg );

				// 람다의 this 캡쳐를 통해 사용가능
				// Tag와 일치하는 위젯컨트롤러에서 사용하는 DataTable 의 행을 가져옴
				// 해당 행을 기반으로 위젯블루프린트에 전달 및 표현 예정
				FUIWidgetRow* Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag);
			}
		}
	);
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

void UOverlayWidgetController::ManaChanged(const FOnAttributeChangeData& Data) const
{
	OnManaChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxManaChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxManaChanged.Broadcast(Data.NewValue);
}
