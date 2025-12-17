#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "AuraEnemy.generated.h"

UCLASS()
class AURA_API AAuraEnemy : public AAuraCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()

public:
	virtual void HighlightActor() override;
	virtual void UnhighlightActor() override;

	// 해당 변수를 블루프린트에서 값을 읽어 테스트를 위해 디버그 드로우 할 예정
	UPROPERTY(BlueprintReadOnly)
	bool bHighlighted = false;
};
