#include "AbilitySystem/AuraAbilitySystemComponent.h"

void UAuraAbilitySystemComponent::AbilityActorInfoSet()
{
	// Dynamic 델리게이트가 아니므로 AddUObject를 통해 바인딩하여야함
	// Effect가 적용될때 동작하는 델리게이트
	// ASC 를 가진 액터(해당 함수를 호출중인 곳 : AuraCharacter,Enemy)가
	// EffectActor로 인해 효과를 적용받을때 호출
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAuraAbilitySystemComponent::EffectApplied);
}

void UAuraAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent,
                                                const FGameplayEffectSpec& EffectSpec,
                                                FActiveGameplayEffectHandle ActiveGameplayEffectHandle)
{
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);

	// 해당 ASC를 가진 액터에 Effect 적용시 AssetTags 를  브로드캐스트
	//현재 OverlayWdigetController 에서 바인딩하여 확인하고있음
	EffectAssetTags.Broadcast(TagContainer);
}
