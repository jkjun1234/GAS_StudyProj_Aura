// AuraCharacter.h
// Alt + o 를 통해 Cpp 코드를 확인중에도 헤더파일/Cpp 파일을 바로 열 수 있다.

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "AuraCharacter.generated.h"


UCLASS()
class AURA_API AAuraCharacter : public AAuraCharacterBase
{
	GENERATED_BODY()

public:
	AAuraCharacter();
};
