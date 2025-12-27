
#include "Player/AuraPlayerState.h"

AAuraPlayerState::AAuraPlayerState()
{
	// 네트워크 동기화 속도 높을수록 빠르게 통신
	NetUpdateFrequency = 100.f;
}
