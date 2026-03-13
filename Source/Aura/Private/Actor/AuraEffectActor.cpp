#include "Actor/AuraEffectActor.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"


// Sets default values
AAuraEffectActor::AAuraEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	// Sphere와 Mesh 제거
	// 블루프린트 내에서 디자이너 영역을 처리할 예정

	SetRootComponent(CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot")));
}


void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();
}

void AAuraEffectActor::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	// 1. 타겟의 ASC(Ability System Component) 가져오기
	// UAbilitySystemBlueprintLibrary를 사용하면 액터가 IAbilitySystemInterface를 구현했는지 자동으로 확인하고 ASC를 반환해 줍니다.
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);

	// 타겟이 ASC를 가지고 있지 않다면 (즉, GAS를 사용하는 액터가 아니라면) 함수를 즉시 종료합니다.
	if (TargetASC == nullptr) return; 

	// 2. 적용할 이펙트 클래스 유효성 검사
	// GameplayEffectClass가 nullptr인 상태로 진행되면 언리얼 엔진이 크래시가 납니다. 
	// 개발 단계에서 디자이너가 클래스 할당을 깜빡한 경우를 빠르게 캐치하기 위해 check() 매크로를 사용합니다.
	check(GameplayEffectClass);
	
	// 3. Effect Context 생성 및 출처 설정
	// 이펙트가 '어떤 상황'에서 '누구'로부터 발생했는지에 대한 맥락(Context) 데이터를 담는 객체입니다.
	FGameplayEffectContextHandle EffectContextHandle = TargetASC->MakeEffectContext();
	
	// 이 이펙트를 발생시킨 주체(Source)가 바로 이 액터(AuraEffectActor)임을 Context에 명시합니다.
	// 나중에 데미지 반사, 처치 기록(Kill log), 혹은 UI 표시 등을 할 때 '누가 이 효과를 줬는지' 추적하기 위해 필수적입니다.
	EffectContextHandle.AddSourceObject(this); 

	// 4. Effect Spec(스펙) 생성
	// GameplayEffect 자체는 변하지 않는 '데이터 템플릿(CDO)'입니다. 이를 타겟에게 실제로 적용하려면 
	// 레벨(Level)이나 컨텍스트 같은 동적인 정보를 담은 '인스턴스화된 데이터'인 Spec을 만들어야 합니다.
	// 1.f는 이펙트의 레벨(Level)을 의미하며, 앞서 만든 ContextHandle을 함께 넘겨줍니다.
	const FGameplayEffectSpecHandle EffectSpecHandle = TargetASC->MakeOutgoingSpec(GameplayEffectClass, 1.f, EffectContextHandle);
	
	// 5. 타겟에게 Effect 최종 적용
	// 생성된 Spec 객체를 타겟의 ASC에 실제로 적용합니다.
	// EffectSpecHandle.Data는 TSharedPtr(스마트 포인터)로 래핑되어 있으므로, Get()으로 포인터를 가져온 뒤 역참조(*)하여 레퍼런스로 넘겨줍니다.
	FActiveGameplayEffectHandle ActiveEffectHandle = TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());

	const bool bIsInfinite = EffectSpecHandle.Data.Get()->Def.Get()->DurationPolicy == EGameplayEffectDurationType::Infinite;

	// 제거 정책이 RemoveEndOverlap/RemoveOnOverlap 일경우 활성화된 이펙트들을 지우기위한 핸들맵에 추가(저장하기위해)
	if (bIsInfinite && InfiniteEffectRemovalPolicy != EEffectRemovalPolicy::DoNotRemove)
	{
		// 무제한 이펙트일경우 활성화 핸들맵에 ASC와 핸들러 추가
		ActiveEffectHandles.Add(ActiveEffectHandle, TargetASC);
	}
}

// Effect 액터 Overlap 시 이펙트 적용 정책에 따라 이펙트 적용
void AAuraEffectActor::OnOverlap(AActor* TargetActor)
{
	if (InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, InstantGameplayEffectClass);
	}
	if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, DurationGameplayEffectClass);
	}
	if (InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClass);
	}
}

// Effect 액터 EndOverlap시 이펙트 적용 정책에 따라 효과 적용
void AAuraEffectActor::OnEndOverlap(AActor* TargetActor)
{
	if (InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, InstantGameplayEffectClass);
	}
	if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, DurationGameplayEffectClass);
	}
	if (InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClass);
	}

	// 제거할 항목 중 무제한 이펙트의 경우와 제거 정책으로 RemoveOnEndOverlap 일때 
	if (InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
		if (!IsValid(TargetASC)) return;

		TArray<FActiveGameplayEffectHandle> HandlesToRemove;
		// EffectHandle들을 조회하여 Overlap이 끝난 EffectHandle과 같은지 키값을 확인후 해당 이펙트 제거
		for (TTuple<FActiveGameplayEffectHandle, UAbilitySystemComponent*> HandlePair : ActiveEffectHandles)
		{
			if (TargetASC == HandlePair.Value)
			{
				// 활성화중인 이펙트를 제거하는데 1개의 스택만 제거
				// -1 일경우 모든 스택을 제거한다.
				TargetASC->RemoveActiveGameplayEffect(HandlePair.Key, 1);
				HandlesToRemove.Add(HandlePair.Key);
			}
		}

		// 제거될 이펙트 목록들을 확인 후 정리 및 제거
		for (FActiveGameplayEffectHandle& Handle : HandlesToRemove)
		{
			ActiveEffectHandles.FindAndRemoveChecked(Handle);
		}
	}
}
