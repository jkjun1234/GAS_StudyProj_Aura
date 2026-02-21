#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AuraUserWidget.generated.h"

UCLASS()
class AURA_API UAuraUserWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* InWidgetController);

	// 위젯들이 연결될 위젯컨트롤러
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> WidgetController;

protected:

	// 블루프린트에서 오버라이드 하여사용할 함수
	// 위젯 컨트롤러를 설정하는 함수
	// SetWidgetController 함수에서 한번 호출해줌
	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet();
};
