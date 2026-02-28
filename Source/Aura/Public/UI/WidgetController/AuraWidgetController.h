#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "UObject/NoExportTypes.h"
#include "AuraWidgetController.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;

// WidgetController에서 사용할 파라미터를 구조체화한것

USTRUCT(BlueprintType)
struct FWidgetControllerParams
{
	GENERATED_BODY()

	FWidgetControllerParams() {}
	FWidgetControllerParams(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
		: PlayerController(PC), PlayerState(PS), AbilitySystemComponent(ASC), AttributeSet(AS){}

	// 생성자에서 초기화 하기위해 아래처럼 선언 후 nullPtr 로 선언해준다.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<APlayerController> PlayerController = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<APlayerState> PlayerState = nullptr;

	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAttributeSet> AttributeSet = nullptr;
};

// 위젯 컨트롤러
// 데이터(어트리뷰트 속성 등)들을 읽어와 해당 위젯컨트롤러를 사용하는 모든 위젯(UserWidget)들에게
// 브로드 캐스트할 의무를 가졌음
// 필요한 정보(데이터)들을 담을수 있는 변수를 사용해야함 

UCLASS()
class AURA_API UAuraWidgetController : public UObject
{
	GENERATED_BODY()

public:
	// 위젯컨트롤러 파라미터 설정
	UFUNCTION(BlueprintCallable)
	void SetWidgetControllerParams(FWidgetControllerParams WCParams);
	
protected:
	// 플레이어 컨트롤러 저장
	UPROPERTY(BlueprintReadWrite, Category="WidgetController")
	TObjectPtr<APlayerController> PlayerController;

	// 플레이어의 상태를 확인하기위한 플레이어스테이트
	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<APlayerState> PlayerState;

	//GAS 사용을 위한 ASC, AttributeSet 가져오기
	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<UAttributeSet> AttributeSet;
};
