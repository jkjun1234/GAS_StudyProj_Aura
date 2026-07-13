# GAS 튜터 커리큘럼 — Aura로 배우는 Gameplay Ability System

전체 **8개 파트 · 39스텝**. 한 스텝 = 한 기능/주제이며, 모든 스텝은 SKILL.md의 "스텝 진행
루프"(학습목표 → 심층 설명 → 빌드 → 에디터 → 테스트 → 직접 해보기 → 진도 갱신 → 다음 안내)를
따른다.

- 표기: 🔍 해부(기존 코드 읽기 중심) · 🛠 구현(새 코드 작성) · 📦 에디터 작업 비중 큼
- 경로 표기: `Public/...` = `Source/Aura/Public/...`. 구현부는 `Source/Aura/Private/` 아래
  같은 경로의 `.cpp`.
- 파일 경로·심볼은 커리큘럼 작성 시점(2026-07) 기준이다. **가르치기 전에 반드시 Read로 현재
  상태를 확인**하고, 달라졌으면 실제 코드를 기준으로 한다.
- 이 프로젝트는 **Druid Mechanics Udemy GAS 강의**를 따라 만들던 부분 체크포인트다. 강의
  완성본이 `DruidMech/GameplayAbilitySystem_Aura`(GitHub)에 있고, 이것이 **정답지이자
  이름·구조의 기준**이다. Part 2 이후 새 클래스/에셋 이름은 아래에 적힌 것과 완성본이 다르면
  **완성본을 따른다**(대부분 이미 일치: `MMC_MaxHealth/MaxMana`, `ExecCalc_Damage`,
  `AuraInputConfig`, `AuraProjectileSpell`, `AuraAIController` 등). 참조·페치 방법과 파트별
  완성본 위치 지도는 `reference/upstream-repo.md`에 있다.
- 완성본에는 이 39스텝에 없는 추가 기능도 있다 — 패시브/소환 어빌리티, 캐릭터 클래스
  (`CharacterClassInfo`), 디버프 Niagara, 루트 등급, 빔 스펠 등. 해당 파트에서 학습자가 원하면
  곁가지로 얹거나 완주 후 확장 과제로 다룬다.

---

## Part 0 — 오리엔테이션 & 큰 그림

### 0.1 🔍 GAS 전체 그림
- 목표: GAS의 핵심 조각 — ASC(AbilitySystemComponent), 어트리뷰트 셋(AttributeSet),
  게임플레이 이펙트(GameplayEffect, GE), 게임플레이 어빌리티(GameplayAbility, GA),
  게임플레이 태그(GameplayTag), 게임플레이 큐(GameplayCue) — 가 각각 무엇이고 어떻게
  맞물리는지 지도를 그린다.
- 재료: 관계 다이어그램(show_widget으로 그려서 보여주기) + "포션을 밟으면 체력이 찬다"를
  GAS 흐름으로 추적(이 프로젝트에 이미 구현된 시나리오).
- 직접 해보기: "적이 파이어볼에 맞아 체력이 깎이고, 화상 데미지가 3초간 이어진다"를 GAS
  용어(ASC/GE/GA/태그/큐)로 문장 재구성.
- 빌드/에디터: 없음(개념 스텝).

### 0.2 🛠 프로젝트 투어 & 빌드 워크플로우
- 목표: Source 폴더 구조와 모듈 시스템, `Source/Aura/Aura.Build.cs`의 의존
  모듈(GameplayAbilities·GameplayTags·GameplayTasks), `Aura.uproject`의 플러그인 설정을
  확인하고, 앞으로 매 스텝 반복할 "빌드 → 에디터 → PIE → 로그" 사이클을 한 번 완주한다.
- 핵심 파일: `Aura.uproject`, `Source/Aura/Aura.Build.cs`, `Source/Aura.Target.cs`,
  `Source/AuraEditor.Target.cs`
- 진행: 튜터가 첫 빌드 실행(성공 확인) → 에디터 백그라운드 실행 → 학습자가 PIE 재생 →
  `Saved/Logs/Aura.log`를 튜터가 열어 함께 읽기.
- 직접 해보기: 로그에서 눈에 띄는 라인 3개를 골라 무슨 의미일지 추측해 보기(튜터가 해설).

---

## Part 1 — 기존 코드 해부 (이미 작성된 코드가 교재)

### 1.1 🔍 캐릭터 계층과 ASC 소유권
- 목표: `AuraCharacterBase` → `AuraCharacter`/`AuraEnemy` 계층과 `IAbilitySystemInterface`,
  그리고 "플레이어의 ASC·AttributeSet은 왜 PlayerState가 소유하고, 적은 왜 자기 자신이
  소유하는가"(수명·리스폰·복제 관점)를 이해한다.
- 핵심 파일: `Public/Character/AuraCharacterBase.h`, `Public/Character/AuraCharacter.h`,
  `Public/Character/AuraEnemy.h`, `Public/Player/AuraPlayerState.h` (+ 각 .cpp)
- 직접 해보기: "적도 PlayerState 방식으로 만들면 무슨 문제가 생길까?"를 수명·리스폰·서버
  부하 관점에서 답해 보기.

### 1.2 🔍 InitAbilityActorInfo — ASC 초기화 타이밍
- 목표: OwnerActor vs AvatarActor 구분, 서버(`PossessedBy`)와
  클라이언트(`OnRep_PlayerState`)에서 초기화가 각각 언제 불리는지, 왜 두 군데 모두 필요한지
  이해한다. 적은 `BeginPlay`에서 자기 자신으로 초기화하는 것과 대비.
- 핵심 파일: `Private/Character/AuraCharacter.cpp`(PossessedBy → InitAbilityActorInfo,
  OnRep_PlayerState), `Private/Character/AuraEnemy.cpp`(BeginPlay),
  `Public/Character/AuraCharacterBase.h`(가상 함수 선언)
- 직접 해보기: 각 함수에 UE_LOG를 심고 PIE 실행 로그로 호출 순서를 실측 → 튜터와 로그 해석.
  (여유가 되면 Play 설정에서 클라이언트 2개로 실행해 서버/클라 차이 관찰)

### 1.3 🔍 AuraAttributeSet — 속성, 복제, 클램핑
- 목표: `FGameplayAttributeData`, `ATTRIBUTE_ACCESSORS` 매크로가 만들어 주는 4종 함수,
  `DOREPLIFETIME_CONDITION_NOTIFY` + `OnRep_*` + `GAMEPLAYATTRIBUTE_REPNOTIFY`의 복제 왕복,
  `PreAttributeChange` 클램핑의 역할과 한계를 이해한다. 이미 선언돼 있는
  `FEffectProperties`/`SetEffectProperties`가 무엇을 캡슐화하는지도 훑는다(Part 4에서 본격 사용).
- 핵심 파일: `Public/AbilitySystem/AuraAttributeSet.h`,
  `Private/AbilitySystem/AuraAttributeSet.cpp`
- 직접 해보기: 클램프 범위를 바꾸거나 로그를 심어, 포션 액터로 Health 변화를 PIE에서 관찰.

### 1.4 🔍 커스텀 ASC — Effect 적용 감지와 태그 브로드캐스트
- 목표: `OnGameplayEffectAppliedDelegateToSelf`에 `EffectApplied`를 바인딩하는 구조,
  Spec에서 `GetAllAssetTags`로 태그를 꺼내 `EffectAssetTags` 델리게이트로 UI까지 흘려보내는
  파이프라인을 이해한다(최근 커밋에서 작업한 바로 그 코드).
- 핵심 파일: `Public/AbilitySystem/AuraAbilitySystemComponent.h`,
  `Private/AbilitySystem/AuraAbilitySystemComponent.cpp`
- 직접 해보기: 이 델리게이트가 서버/클라 중 어디서 불릴지 예측하고 로그로 검증.

### 1.5 🔍 AuraEffectActor — GE를 세계에 배치하는 법
- 목표: Instant/Duration/Infinite GE의 차이, `ApplyEffectToTarget`의 4단계(ASC 획득 →
  EffectContext → EffectSpec → ApplyGameplayEffectSpecToSelf), 적용/제거 정책 enum,
  Infinite 제거를 위한 `ActiveEffectHandles` 관리 방식을 이해한다.
- 핵심 파일: `Public/Actor/AuraEffectActor.h`, `Private/Actor/AuraEffectActor.cpp`
- 직접 해보기: "불장판(밟는 동안 초당 데미지, 나가면 즉시 중단)"을 만들려면 어떤 GE
  타입+정책 조합이어야 하는지 설계해 보기(구현은 Part 4 이후).

### 1.6 🔍 UI 아키텍처 — WidgetController 패턴
- 목표: HUD → WidgetController → UserWidget 단방향 의존 구조, `FWidgetControllerParams`,
  `BroadcastInitialValues`/`BindCallbacksToDependencies`, `FUIWidgetRow` +
  `GetDataTableRowByTag` 템플릿으로 태그→메시지 데이터를 찾는 경로까지, 속성 값이 화면에
  닿는 전체 흐름을 이해한다.
- 핵심 파일: `Public/UI/HUD/AuraHUD.h`, `Public/UI/WidgetController/AuraWidgetController.h`,
  `Public/UI/WidgetController/OverlayWidgetController.h`(+ .cpp),
  `Public/UI/Widget/AuraUserWidget.h`,
  에셋 `Content/Blueprints/UI/Data/DT_MessageWidgetData.uasset`
- 직접 해보기: "Mana 숫자가 안 바뀐다면 어디부터 의심할까?" — 데이터 경로를 따라 디버깅
  순서를 말해 보기.

### 1.7 🔍 입력과 상호작용 — Enhanced Input & CursorTrace
- 목표: IMC(InputMappingContext)/InputAction 바인딩 구조, `CursorTrace`의 5가지
  케이스(A~E) 하이라이트 분기, `IEnemyInterface`, CustomDepth + PostProcess로 외곽선이
  그려지는 원리를 이해한다.
- 핵심 파일: `Public/Player/AuraPlayerController.h`,
  `Private/Player/AuraPlayerController.cpp`, `Public/Interaction/EnemyInterface.h`
- 직접 해보기: 케이스 A~E 중 둘을 골라 실제 커서 움직임으로 재현하고 어떤 분기인지 설명.

### 1.8 🔍 GameplayTag 등록과 데이터 주도 UI 메시지
- 목표: 태그 등록 3경로(ini / DataTable / 에디터), `Config/DefaultGameplayTags.ini` 내용,
  GE 에셋 태그 → `EffectAssetTags` 브로드캐스트 → `FUIWidgetRow` 매칭 → 화면 메시지까지
  1.4+1.6을 총정리한다.
- 핵심 파일: `Config/DefaultGameplayTags.ini`,
  `Content/Blueprints/AbilitySystem/GameplayTags/DT_PrimaryAttributes.uasset`,
  `Content/Blueprints/UI/Data/DT_MessageWidgetData.uasset`
- 직접 해보기 📦: 새 태그 `Message.Sample`을 등록하고 DataTable 행을 추가해, 새 EffectActor를
  밟으면 새 메시지가 뜨게 만들기(에디터 작업 — Part 1 졸업 과제).

---

## Part 2 — 속성 확장 & GameplayEffect 심화

### 2.1 🛠 Primary 속성 4종
- 목표: Strength/Intelligence/Resilience/Vigor를 AttributeSet에 추가(선언·복제·OnRep)하며
  1.3에서 배운 패턴을 손에 익힌다. `Attributes.Primary.*` 태그 등록.
- 작업: Strength/Intelligence/Resilience는 튜터와 함께 추가.
- 직접 해보기: **Vigor는 학습자가 처음부터 끝까지 스스로 추가**(튜터가 빌드로 검증).

### 2.2 🛠 Secondary 파생 속성 + MMC
- 목표: Armor/ArmorPenetration/BlockChance/CriticalHitChance/CriticalHitDamage/
  CriticalHitResistance/HealthRegeneration/ManaRegeneration/MaxHealth/MaxMana를 추가하고,
  AttributeBased 계산과 커스텀 계산 클래스(MMC, ModifierMagnitudeCalculation)의 차이를
  배운다(예: MMC_MaxHealth가 Vigor+레벨을 참조).
- 작업 📦: 속성 추가 + `MMC_MaxHealth` C++ 작성 + GE_SecondaryAttributes(Infinite) 에디터 제작.
- 직접 해보기: `MMC_MaxMana`를 스스로(Intelligence 기반).

### 2.3 🛠 기본값 초기화 파이프라인
- 목표: "Primary는 Instant GE → Secondary는 Infinite GE(자동 갱신) → Vital(Health/Mana)은
  마지막에 Instant"라는 초기화 순서와 그 이유(파생 의존성)를 이해하고 구현한다.
- 작업 📦: CharacterBase에 `InitializeDefaultAttributes`/`ApplyEffectToSelf`, GE 3종
  제작·연결. 기존 임시 초기화 방식이 있다면 정리.
- 직접 해보기: 초기화 순서를 일부러 바꿔 무엇이 깨지는지 관찰하고 원복.

### 2.4 🔍 Modifier / MMC / ExecCalc 선택 기준
- 목표: 값 계산 3방식의 선택 기준 정리 + `PreAttributeChange` vs
  `PostGameplayEffectExecute` 역할 구분(Part 4 준비). 엔진 헤더
  `GameplayEffectExecutionCalculation.h`를 가볍게 훑는다.
- 직접 해보기: "크리티컬 확률이 적의 크리 저항에 깎이는 데미지"는 셋 중 무엇으로 구현해야
  할지 근거와 함께 답하기.

---

## Part 3 — GameplayAbility 기초

### 3.1 🛠 UAuraGameplayAbility와 어빌리티 부여
- 목표: GA 서브클래스, `FGameplayAbilitySpec`, 서버에서 `GiveAbility`로 시작 어빌리티를
  부여하는 흐름을 배운다.
- 작업 📦: `AuraGameplayAbility` C++ + CharacterBase `AddCharacterAbilities` +
  StartupAbilities 배열 + 화면 문자열을 찍는 테스트용 BP GA.
- 직접 해보기: 두 번째 테스트 GA를 만들어 스스로 부여.

### 3.2 🛠 InputTag 기반 입력→어빌리티 연결
- 목표: 키를 하드코딩하지 않고 InputTag(`InputTag.LMB/.RMB/.1~.4`)로 GA와 입력을 느슨하게
  묶는 데이터 주도 설계를 배운다.
- 작업 📦: `AuraInputConfig`(DataAsset), `AuraInputComponent`(제네릭 바인딩),
  PlayerController에 `AbilityInputTagPressed/Held/Released`, ASC에 활성화 로직, IA/IMC 제작.
- 직접 해보기: 숫자키 2에 새 InputTag를 스스로 배선.

### 3.3 🛠 Cost & Cooldown
- 목표: AbilityTags 체계, Cost GE(마나 소모)와 Cooldown GE(태그 기반 시간 잠금),
  `CommitAbility`가 하는 일을 배운다.
- 작업 📦: 테스트 GA에 Cost/Cooldown GE 연결, 마나 부족·쿨다운 중 활성 실패 확인.
- 직접 해보기: 쿨다운 남은 시간을 화면에 표시해 보기(힌트: GetCooldownTimeRemaining).

### 3.4 🔍 어빌리티 라이프사이클 & 예측 개요
- 목표: TryActivate → CanActivate → Activate → Commit → End 전체 흐름,
  InstancingPolicy, NetExecutionPolicy, 예측(Prediction)이 왜 필요한지 개요 수준으로 이해.
- 재료: 3.1~3.3에서 만든 코드 + 엔진 `GameplayAbility.h` 발췌.
- 직접 해보기: 자기 GA 하나의 라이프사이클을 로그로 추적해 순서도로 정리.

---

## Part 4 — 전투와 데미지

### 4.1 🛠 Damage 메타 속성과 PostGameplayEffectExecute
- 목표: 복제되지 않는 메타 속성(IncomingDamage) 개념, `PostGameplayEffectExecute`에서
  데미지를 Health에 반영하고 0 이하일 때 사망 처리로 넘기는 구조. 1.3에서 본
  `FEffectProperties`가 여기서 본격 활약한다.
- 작업: IncomingDamage 추가, PostGameplayEffectExecute 데미지 처리, CombatInterface·Die 골격.
- 직접 해보기: 받은 데미지 숫자를 화면 디버그 메시지로 띄우기.

### 4.2 🛠 ExecCalc_Damage — 본격 데미지 공식
- 목표: ExecutionCalculation에서 소스/타깃 속성 캡처(Armor, BlockChance, ArmorPenetration,
  Crit 계열), 공식 조립, GE에 등록하는 방법을 배운다.
- 작업 📦: `ExecCalc_Damage` C++ + GE_Damage 제작.
- 직접 해보기: "블록 성공 시 데미지 절반" 규칙을 스스로 추가.

### 4.3 🛠 SetByCaller와 레벨 스케일링
- 목표: `AssignTagSetByCallerMagnitude`로 GA가 GE에 런타임 값을 주입하는 법,
  ScalableFloat+커브테이블로 어빌리티 레벨별 데미지를 데이터화하는 법.
- 작업 📦: Damage 태그, GA에서 SetByCaller 주입, CT_Damage 커브테이블.
- 직접 해보기: 레벨 1→2 데미지 변화를 PIE에서 검증.

### 4.4 🛠 HitReact와 사망 연출
- 목표: `Effects.HitReact` 태그 부여/제거를 `RegisterGameplayTagEvent`로 감지해 몽타주 재생,
  사망 시 래그돌 + 디졸브(Dissolve) 머티리얼 연출(기존 HitReact 애니메이션 에셋 활용).
- 작업 📦: HitReact 처리, `Die`/`MulticastHandleDeath`, 디졸브 타임라인.
- 직접 해보기: 피격 경직 중 이동을 잠깐 막아 보기(힌트: 태그로 입력/이동 차단).

---

## Part 5 — 어빌리티 구현: 투사체·AoE·근접

### 5.1 🛠 AuraProjectile + FireBolt
- 목표: 투사체 액터(ProjectileMovement, 충돌, 수명), 몽타주 + AnimNotify 타이밍에 서버
  스폰, CombatInterface로 소켓 위치 얻기, 커서 방향 타겟팅, 명중 시 GE_Damage 적용까지 —
  첫 실전 어빌리티를 완성한다(기존 FireBolt 애니메이션 활용).
- 작업 📦: `AuraProjectile` C++, `AuraProjectileSpell`(GA), BP_FireBolt + 캐스팅 몽타주 연결.
- 직접 해보기: 투사체 속도/수명/중력 파라미터를 바꿔 손맛 튜닝.

### 5.2 🛠 GameplayCue로 임팩트 연출
- 목표: 시각/청각 피드백을 GameplayCue(태그 기반, 자동 복제)로 분리하는 이유와 방법.
  GameplayCueNotify로 임팩트 파티클+사운드.
- 작업 📦: `GameplayCue.FireBolt.Impact` 태그 + CueNotify 에셋, 투사체 명중 시 실행.
- 직접 해보기: 발사 순간용 Cue를 하나 더 추가.

### 5.3 🛠 (심화 실습) 두 번째 스펠 — AoE
- 목표: 지금까지 배운 GA/GE/ExecCalc/Cue 조합을 학습자가 주도적으로 재조립한다. 튜터는 설계
  리뷰와 막힌 곳 힌트만 제공. 범위 타겟팅(커서 위치), 다단 히트 또는 지연 폭발 — 기존
  ArcaneShards/Shock 계열 에셋 활용.
- 직접 해보기: **이 스텝 전체가 직접 해보기**(설계 → 구현 → 시연). 완성 후 튜터가 코드 리뷰.

### 5.4 🛠 근접 공격
- 목표: 투사체 없는 공격 — 몽타주 노티파이 시점에 소켓 기준 오버랩/트레이스로 대상 판정,
  동일한 GE_Damage 재사용(적 기본 공격의 토대가 된다).
- 직접 해보기: 판정 반경을 조절해 히트 체감 개선.

---

## Part 6 — 적 AI

### 6.1 🛠 AuraAIController + Behavior Tree
- 목표: AIController/BehaviorTree/Blackboard 3요소의 관계, 적이 플레이어를 인지하고
  추격하는 최소 트리를 만든다.
- 작업 📦: `AuraAIController` C++, BT_Enemy/BB_Enemy, AuraEnemy에서 RunBehaviorTree.
- 직접 해보기: "일정 거리 밖이면 제자리 복귀" 브랜치 추가.

### 6.2 🛠 적의 어빌리티 사용
- 목표: 적에게도 같은 GAS 파이프라인(GiveAbility → BTTask에서 TryActivate)을 태워
  플레이어를 공격하게 한다(고블린 근접, 원거리 적 등 에셋 매칭).
- 작업 📦: BTTask_Attack, 적 GA 연결.
- 직접 해보기: 공격 간격을 BT 대기(Wait)가 아니라 Cooldown GE로 걸어 보기.

### 6.3 🛠 적 체력바와 레벨별 스탯
- 목표: WidgetComponent 월드 체력바에 델리게이트 바인딩(1.6 패턴의 미니 버전), 적 레벨 →
  속성 초기화를 커브테이블로 데이터화.
- 작업 📦: 체력바 위젯, 적의 InitializeDefaultAttributes 오버라이드(레벨 파라미터).
- 직접 해보기: 레벨 3 적과 레벨 1 적을 나란히 배치해 스탯 차이 검증.

---

## Part 7 — 성장 시스템 & 메뉴 UI

### 7.1 🛠 경험치 파이프라인
- 목표: IncomingXP 메타 속성, 적 처치 → XP 지급 이벤트, LevelUpInfo 데이터에셋(레벨별 요구
  XP), PlayerState의 XP/Level 복제와 변경 델리게이트.
- 직접 해보기: 처치 시 XP 획득을 로그+화면으로 표시.

### 7.2 🛠 레벨업
- 목표: XP 누적 → 레벨업 판정 → AttributePoints/SpellPoints 지급 → MaxHealth/MaxMana
  재계산(2.2 MMC가 빛나는 순간) → 레벨업 이펙트.
- 직접 해보기: 레벨업 시 체력/마나 전량 회복 규칙 추가.

### 7.3 🛠 속성 메뉴 (AttributeMenu)
- 목표: 두 번째 WidgetController를 만들며 1.6 패턴을 일반화한다. 태그→속성 매핑
  데이터에셋(AttributeInfo)으로 UI 행을 데이터 주도로 구성, 포인트 소비 버튼(서버 검증).
- 작업 📦: `AttributeMenuWidgetController` C++, WBP_AttributeMenu.
- 직접 해보기: 속성 하나(예: Resilience)의 행 전체를 스스로 배선.

### 7.4 🛠 스펠 메뉴와 장착
- 목표: 스펠 상태(Locked/Eligible/Unlocked/Equipped) 관리, 스펠 포인트로 언락, 슬롯
  (InputTag)에 장착/교체 — 3.2의 InputTag 설계가 회수되는 지점.
- 작업 📦: `SpellMenuWidgetController`, 어빌리티 상태 태그 관리, WBP_SpellMenu.
- 직접 해보기: 이미 장착된 스펠끼리 슬롯 스왑 케이스 처리.

---

## Part 8 — 게임 완성과 배포

### 8.1 🛠 메인 메뉴와 게임 플로우
- 목표: 메인 메뉴 맵/위젯, 새 게임·계속·종료, 맵 전환(OpenLevel), GameMode 정리.
- 작업 📦: 메뉴 맵 + WBP_MainMenu.
- 직접 해보기: 메뉴에 조작법 안내 페이지 추가.

### 8.2 🛠 세이브 & 로드
- 목표: `USaveGame` 서브클래스, 저장 항목 결정(레벨/XP/포인트/속성/장착 스펠/체크포인트
  위치), 저장 시점(체크포인트) 설계, 로드 시 GAS 상태 복원 순서.
- 직접 해보기: 저장 항목 하나(예: 배운 스펠 목록)를 스스로 추가.

### 8.3 📦 레벨 구성 — 플레이 가능한 던전
- 목표: 모듈러 던전 키트로 15~20분 플레이 루프(입구 → 전투 구간 → 포션 보급 → 중간 보스)를
  구성하고, 적 스폰·EffectActor 픽업·체크포인트를 배치한다.
- 직접 해보기: 이 스텝 대부분이 학습자 주도 레벨 디자인(튜터는 배치 가이드라인과 리뷰 제공).

### 8.4 🛠 사운드·폴리시·밸런싱
- 목표: 사운드(피격/시전/사망/BGM) 연결, 커브테이블 기반 밸런스 일괄 조정, 로그 워닝 정리
  등 마감 스윕.
- 직접 해보기: 직접 플레이해 "너무 쉽다/어렵다" 구간을 찾아 밸런스 패치.

### 8.5 🛠 Windows Shipping 패키징
- 목표: 패키징 설정(기본 맵, 포함 맵 목록, Shipping 구성), RunUAT BuildCookRun 실행(튜터가
  직접), 흔한 쿠킹 에러 대응, 실행파일 단독 플레이 검증.
- 산출물: `Packaged/Windows/Aura.exe`
- 직접 해보기: 패키징 산출물을 다른 폴더로 옮겨 실행해 의존성 확인.

### 8.6 📦 배포와 포트폴리오
- 목표: itch.io 페이지 생성 → zip 업로드(또는 butler CLI), 소개문/스크린샷/조작법 작성,
  리포지토리 README를 포트폴리오용으로 정리(배운 GAS 개념 요약 포함).
- 직접 해보기: "이 프로젝트에서 배운 것" 섹션을 스스로 작성 — 튜터가 첨삭.
- 완주 시: 진도 파일에 수료 기록 🎉
