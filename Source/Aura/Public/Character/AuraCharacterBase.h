#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "AuraCharacterBase.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;

UCLASS()
class AURA_API AAuraCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AAuraCharacterBase();

	// Getter
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const { return AttributeSet; }

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category="Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;

	// 어빌리티 시스템 컴포넌트
	// 액터와 시스템(GAS)을 연결하는 역할
	// Attribute, Ability, Gameplay Effect 적용 및 처리, 상태 관리 등 모든 상호작용을 담당
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	// 어트리뷰트 셋
	// 속성 집합으로(캐릭터나 객체의 능력치로 HP,MP 공격력 등 을 묶음으로 관리하는 데이터 집합
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	// ASC의 EffectApplied 델리게이트를 적용하는 함수 ASC->AbilityActorInfoSet() 을 실행
	// 기본적인 액터의 초기값을 초기화
	// 캐릭터, 적 구분하여 초기화를 구현하기위해 Virtual로 선언
	virtual void InitAbilityActorInfo();
};
