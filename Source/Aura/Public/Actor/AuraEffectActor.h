#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"	//FActiveGameplayEffectHandle 을 사용하기 위한 헤더
#include "GameFramework/Actor.h"
#include "AuraEffectActor.generated.h"

class USphereComponent;


// 이펙트 적용 정책으로 해당 이펙트가 적용될때를 설정
UENUM(BlueprintType)
enum class EEffectApplicationPolicy : uint8
{
	ApplyOnOverlap,
	ApplyOnEndOverlap,
	DoNotApply
};

// 이펙트 제거 정책으로 해당 이펙트가 제거될떄를 설정
UENUM(BlueprintType)
enum class EEffectRemovalPolicy : uint8
{
	RemoveOnOverlap,
	RemoveOnEndOverlap,
	DoNotRemove
};

UCLASS()
class AURA_API AAuraEffectActor : public AActor
{
	GENERATED_BODY()

public:
	AAuraEffectActor();

protected:
	virtual void BeginPlay() override;

	// 블루프린트에서 호출할 효과 적용함수
	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass);

	UFUNCTION(BlueprintCallable)
	void OnOverlap(AActor* TargetActor);
	
	UFUNCTION(BlueprintCallable)
	void OnEndOverlap(AActor* TargetActor);

	// 오버랩될시 이펙트 제거용 토글
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Applied Effects")
	bool bDestroyOnEffectRemoval = false;
	
	// 즉시 적용하는 효과를 담는 변수
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	EEffectApplicationPolicy InstantEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;
	
	// 주기동안 효과 적용하는 Effect를 담는 변수
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	TSubclassOf<UGameplayEffect> DurationGameplayEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	EEffectApplicationPolicy DurationEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;
	
	// 무한 지속하는 Effect
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	TSubclassOf<UGameplayEffect> InfiniteGameplayEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	EEffectApplicationPolicy InfiniteEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;

	// 무한 지속 Effect를 제거하기위한 정책
	// 이펙트가 겹칠때 제거
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	EEffectRemovalPolicy InfiniteEffectRemovalPolicy = EEffectRemovalPolicy::RemoveOnOverlap;

	// 활성화중인 Effect 를 담고있는 핸들러  
	TMap<FActiveGameplayEffectHandle, UAbilitySystemComponent*> ActiveEffectHandles;

	// EffectActor 레벨
	// 레벨에 따른 효과 적용값(FloatCurve 사용)을 다르게 하기 위해 사용
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	float ActorLevel =1.f;
};
