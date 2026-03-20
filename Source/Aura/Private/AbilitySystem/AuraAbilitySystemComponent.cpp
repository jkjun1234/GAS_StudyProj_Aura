// Fill out your copyright notice in the Description page of Project Settings.


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

	for (const FGameplayTag& Tag : TagContainer)
	{
		// TODO: 태그를 위젯컨트롤러에 전달(브로드캐스트)

		const FString Msg = FString::Printf(TEXT("GE Tag: %s"), *Tag.ToString());
		// 키 값으로 -1을 주는 경우 최신 메세지가 지난 메세지를 가리지않음 
		GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Blue, Msg );
	}
}
