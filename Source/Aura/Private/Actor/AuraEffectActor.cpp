#include "Actor/AuraEffectActor.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Components/SphereComponent.h"

// Sets default values
AAuraEffectActor::AAuraEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);

	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->SetupAttachment(GetRootComponent());
}

void AAuraEffectActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                 const FHitResult& SweepResult)
{
	//TODO: 여기서 게임플레이 이펙트를 적용할 예정.
	//현재는 const를 사용하지않고 임의로 값을 변경하는 사례를 보고자함
	//
	// AbilitySystemInterface 가지고있는지 확인
	if (IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(OtherActor))
	{
		// GetAttributeSet 은 const 형으로 반환하므로 아래와 같이 const 형으로 받아줘야함
		// AttributeSet의 속성을 제어하기 위해 오버랩된 액터의 AttributeSet을 가져옴
		const UAuraAttributeSet* AuraAttributeSet =
		Cast<UAuraAttributeSet>(ASCInterface->GetAbilitySystemComponent()->GetAttributeSet(UAuraAttributeSet::StaticClass()));

		// 캡슐화를 깨뜨려서 AttributeSet의 값이 변경되는것을 보고자함 원래는 위험한 행위로 하지말것
		UAuraAttributeSet* MutableAuraBute = const_cast<UAuraAttributeSet*>(AuraAttributeSet);
		MutableAuraBute->SetHealth(AuraAttributeSet->GetHealth() + 25.f);
		MutableAuraBute->SetMana(AuraAttributeSet->GetMana() - 25.f);
		Destroy();
	}
}

void AAuraEffectActor::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AAuraEffectActor::OnOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &AAuraEffectActor::EndOverlap);
}
