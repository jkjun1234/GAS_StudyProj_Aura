// AuraCharacter.cpp

#include "Character/AuraCharacter.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/AuraPlayerController.h"
#include "Player/AuraPlayerState.h"
#include "UI/HUD/AuraHUD.h"


AAuraCharacter::AAuraCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement = true; // 캐릭터 회전 이동 가능으로 설정
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f); // 캐릭터가 Yaw 축으로 400의 회전속도로 설정
	// TopDown 게임의 초기 설정 
	GetCharacterMovement()->bConstrainToPlane = true; // 캐릭터를 평면 이동으로 제한 
	GetCharacterMovement()->bSnapToPlaneAtStart = true; // 캐릭터 이동 시작시 평면에 스냅으로 설정

	// 컨트롤러의 회전을 사용못하도록 설정
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
}

void AAuraCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// 서버에서 ASC 액터 정보를 초기화
	InitAbilityActorInfo();
}

void AAuraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// 클라이언트에도 ASC 액터 정보 초기화
	InitAbilityActorInfo();
}

void AAuraCharacter::InitAbilityActorInfo()
{
	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);

	// OwnerActor 는 해당 플레이어 캐릭터가 가진 State를 AvatarActor는 현재 캐릭터 클래스를 넘겨준다.
	// OwnerActor : 서버주체로 가지고있을 액터,
	// AvatarActor : 월드에서 보여질 아바타 액터
	AuraPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(AuraPlayerState, this);

	// ASC를 가져와 ActorInfo를 설정
	Cast<UAuraAbilitySystemComponent>(AuraPlayerState->GetAbilitySystemComponent())->AbilityActorInfoSet();
	
	// 액터정보를 초기화 후 캐릭터 베이스에 있는 ASC 와 AttributeSet을 PlayerState에 있는 것으로 가져온다.
	AbilitySystemComponent = AuraPlayerState->GetAbilitySystemComponent();
	AttributeSet = AuraPlayerState->GetAttributeSet();

	// Check 로 컨트롤러를 확인하지 않는 이유
	// 컨트롤러는 멀티플레이 게임일경우 다른 캐릭터의 컨트롤러는 Null을 가지므로
	// Check를 통해 검사할경우 무조건 크래쉬 나기때문
	if (AAuraPlayerController* AuraPlayerController = Cast<AAuraPlayerController>(GetController()))
	{
		// AuraHUD를 가져와 Overlay 위젯을 초기화
		if (AAuraHUD* AuraHUD = Cast<AAuraHUD>(AuraPlayerController->GetHUD()))
		{
			AuraHUD->InitOverlay(AuraPlayerController, AuraPlayerState, AbilitySystemComponent, AttributeSet);
		}
	}
}
