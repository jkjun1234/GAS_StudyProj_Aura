// OverlayWidgetController.h

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "OverlayWidgetController.generated.h"

// 블루프린트에서도 사용을 위해 다이나믹 사용 값을 하나의 파라미터로 전달
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangeSignature, float, NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChangeSignature, float, NewMaxHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnManaChangeSignature, float, NewMana);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxManaChangeSignature, float, NewMaxMana);


/**
 * 
 */
UCLASS(BlueprintType, Blueprintable) // 블루프린트에서 캐스팅할수있도록 허용
class AURA_API UOverlayWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()

public:
	// 브로드캐스팅 함수 오버라이드
	virtual void BroadcastInitialValues() override;
	// 델리게이트에 콜백을 바인딩하는 함수
	virtual void BindCallbacksToDependencies() override;

	// 최대 체력을 전달할 델리게이트들
	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnHealthChangeSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnMaxHealthChangeSignature OnMaxHealthChanged;

	// 마나값 변화를 전달할 델리게이트
	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnManaChangeSignature OnManaChanged;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnMaxManaChangeSignature OnMaxManaChanged;
	
protected:
	// 콜백함수에서 값변경시 브로드캐스트하는 함수
	void HealthChanged(const FOnAttributeChangeData& Data) const;
	void MaxHealthChanged(const FOnAttributeChangeData& Data) const;
	void ManaChanged(const FOnAttributeChangeData& Data) const;
	void MaxManaChanged(const FOnAttributeChangeData& Data) const;
};
