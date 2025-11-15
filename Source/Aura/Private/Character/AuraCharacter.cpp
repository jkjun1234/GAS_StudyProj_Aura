// AuraCharacter.cpp

#include "Character/AuraCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"


AAuraCharacter::AAuraCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;	// 캐릭터 회전 이동 가능으로 설정
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);	// 캐릭터가 Yaw 축으로 400의 회전속도로 설정
	// TopDown 게임의 초기 설정 
	GetCharacterMovement()->bConstrainToPlane = true;	// 캐릭터를 평면 이동으로 제한 
	GetCharacterMovement()->bSnapToPlaneAtStart = true;	// 캐릭터 이동 시작시 평면에 스냅으로 설정

	// 컨트롤러의 회전을 사용못하도록 설정
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
}
