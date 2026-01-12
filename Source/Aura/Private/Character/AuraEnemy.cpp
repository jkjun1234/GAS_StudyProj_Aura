#include "Character/AuraEnemy.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Aura/Aura.h"

/*
 * 적 기본 캐릭터 HighLight/UnHighLight 기능 구현
 * 무기 Weapon 메쉬(AuraCahracterBase에서 구현)와 SkeletalMesh에 붉은 아웃라인을 표시
 */

AAuraEnemy::AAuraEnemy()
{
	// 라인트레이스에 감지되기 위해 해당 콜리전을 Block처리해준다.
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	// 적 캐릭터에서 사용하기 위한 어빌리티 설정
	// 플레이어 캐릭터는 플레이어 스테이트에서 관리
	// Aura 프로젝트에서 생성한 어빌리티 시스템 생성
	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);	// Replicate 설정

	// 적의 속성 세트
	AttributeSet = CreateDefaultSubobject<UAttributeSet>("AttributeSet");
}

void AAuraEnemy::HighlightActor()
{
	bHighlighted = true;
	
	// 캐릭터 하이라이트
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(250);
	
	// 무기 하이라이트
	Weapon->SetRenderCustomDepth(true);
	Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
}

void AAuraEnemy::UnhighlightActor()
{
	bHighlighted = false;
	GetMesh()->SetRenderCustomDepth(false);
	GetMesh()->SetCustomDepthStencilValue(0);

	Weapon->SetRenderCustomDepth(false);
	Weapon->SetCustomDepthStencilValue(0);
}
