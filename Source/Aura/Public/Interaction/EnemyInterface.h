#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EnemyInterface.generated.h"


UINTERFACE(MinimalAPI)
class UEnemyInterface : public UInterface
{
	GENERATED_BODY()
};

class AURA_API IEnemyInterface
{
	GENERATED_BODY()

public:
	// 순수 가상함수로 자식 클래스는 반드시 오버라이드 해야함
	virtual void HighlightActor() = 0;
	virtual void UnhighlightActor() = 0;
};
