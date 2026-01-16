
#include "Player/AuraPlayerState.h"

#include "AttributeSet.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"

AAuraPlayerState::AAuraPlayerState()
{
	// Aura 프로젝트에서 생성한 어빌리티 시스템 생성
	// 플레이어 캐릭터가 관리할 어빌리티 시스템으로 플레이어 스테이트에서 관리
	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);	// Replicate 설정
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);	// 1인 플레이에 적합

	// 적의 속성 세트
	AttributeSet = CreateDefaultSubobject<UAttributeSet>("AttributeSet");
	
	// 네트워크 동기화 속도 높을수록 빠르게 통신
	SetNetUpdateFrequency(100.f);
}

UAbilitySystemComponent* AAuraPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
