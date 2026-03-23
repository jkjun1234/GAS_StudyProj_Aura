// OverlayWidgetController.h

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "OverlayWidgetController.generated.h"

class UAuraUserWidget;

// 블루프린트에서도 사용을 위해 다이나믹 사용 값을 하나의 파라미터로 전달
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangeSignature, float, NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChangeSignature, float, NewMaxHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnManaChangeSignature, float, NewMana);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxManaChangeSignature, float, NewMaxMana);

// 데이터 테이블 행 정의
USTRUCT(BlueprintType)
struct FUIWidgetRow : public FTableRowBase
{
	GENERATED_BODY()

	// 메세지 출력할 태그
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag MessageTag = FGameplayTag();

	// 메세지 내용
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Message = FText();

	// 메세지를 출력할 위젯
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UAuraUserWidget> MessageWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* Image = nullptr;
};

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
	// WidgetController 에서 사용하기 위한 데이터 테이블 추가
	// 해당 데이터 테이블에 이펙트 태그들을 가지고있으며 어떤 메세지를 출력할지에 대한 정보를 담는
	// 데이터 테이블을 에디터에서 적용한다(FUIWidgetRow 행타입을 가진 데이터 테이블).
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widget Data")
	TObjectPtr<UDataTable> MessageWidgetDataTable;
	
	// 콜백함수에서 값변경시 브로드캐스트하는 함수
	void HealthChanged(const FOnAttributeChangeData& Data) const;
	void MaxHealthChanged(const FOnAttributeChangeData& Data) const;
	void ManaChanged(const FOnAttributeChangeData& Data) const;
	void MaxManaChanged(const FOnAttributeChangeData& Data) const;

	// DataTable의 행을 반환 (행 유형(FUIWidgetRow과 같은 행 상관없이 값을 읽고 반환)
	// 이펙트에셋의 MessageTag를 읽어 매치되는 데이터 테이블 행을 반환
	template<typename T>
	T* GetDataTableRowByTag(UDataTable* DataTable, const FGameplayTag& Tag);
};

template <typename T>
T* UOverlayWidgetController::GetDataTableRowByTag(UDataTable* DataTable, const FGameplayTag& Tag)
{
	// Data 테이블 내에서 TagName 을 읽어들여와 반환
	return DataTable->FindRow<T>(Tag.GetTagName(), TEXT(""));
}
