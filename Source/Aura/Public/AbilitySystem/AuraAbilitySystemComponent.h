#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AuraAbilitySystemComponent.generated.h"

// Effect Asset Tag들을 브로드캐스트 하기위한 델리게이트
DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAssetTags, const FGameplayTagContainer& /*AssetTags*/ );

UCLASS()
class AURA_API UAuraAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	// AbilityActor 정보 설정
	void AbilityActorInfoSet();

	FEffectAssetTags EffectAssetTags;
protected:
	// Effect 적용되었을때를 알리기위한 함수
	void EffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec,
	                   FActiveGameplayEffectHandle ActiveGameplayEffectHandle);
};
