# 완성본 참조 저장소 (정답지) — DruidMech/GameplayAbilitySystem_Aura

이 프로젝트는 Druid Mechanics의 Udemy GAS 강의를 따라 만들던 것으로, **아직 완강 전의 부분
체크포인트**다. 강의 완성본이 아래 공개 저장소에 있다.

- URL: https://github.com/DruidMech/GameplayAbilitySystem_Aura
- 구조: **단일 `main` 브랜치**(브랜치·태그로 강의를 나누지 않음). 진행 과정은 **약 394개의
  커밋 히스토리**에 순서대로 기록돼 있다 → 커밋 로그 = 강의가 기능을 쌓아 올린 순서,
  `main` HEAD = 최종 완성본.
- 완성본 Source 규모: 약 140개 `.h/.cpp`, 폴더 `AbilitySystem / Actor / AI / Character /
  Checkpoint / Game / Input / Interaction / Player / UI`.
- 현재 사용자 체크포인트: 약 15개 파일, 폴더 `AbilitySystem / Actor / Character / Game /
  Interaction / Player / UI`. → **AI · Input · Checkpoint 폴더가 아직 없고**, AbilitySystem이
  훨씬 작다. 커리큘럼 Part 1 초반에 해당한다.

## 이 저장소를 쓰는 목적
1. **정답지(answer key)**: 구현 스텝에서 "강의는 이 기능을 정확히 어떻게 짰는가"의 기준.
2. **이름·구조 기준(source of truth)**: 새 클래스/폴더 이름은 **완성본과 동일하게** 지어
   사용자의 프로젝트가 강의와 계속 호환되게 한다(커리큘럼의 제안 이름과 다르면 완성본을 따른다).
3. **빌드 순서 참고**: 한 기능이 어떤 작은 단계들로 쌓였는지 커밋 히스토리로 확인.
4. **막힘 해소**: 사용자가 만든 코드가 완성본과 어디서 갈라지는지 대조해 디버깅.

## 가져오는 법 (튜터가 필요할 때만)

### A. 원문 파일 페치 — 기본 수단 (정확한 바이트, 요약 안 거침)
raw.githubusercontent에서 특정 파일을 그대로 받아 스크래치패드에 저장한 뒤 Read한다.
(WebFetch는 요약 모델을 거쳐 코드가 뭉개지므로, 코드 원문은 반드시 이 방식으로.)

```powershell
$ProgressPreference='SilentlyContinue'
$rel  = 'Source/Aura/Public/AbilitySystem/AuraAttributeSet.h'   # 저장소 기준 상대경로
$dest = "C:\Users\jun\AppData\Local\Temp\claude\E--UE5-PortfolioPrj-Aura\7f10adab-57b5-4e0d-a518-f09709c5c195\scratchpad\upstream\" + (Split-Path $rel -Leaf)
New-Item -ItemType Directory -Force (Split-Path $dest) | Out-Null
Invoke-WebRequest "https://raw.githubusercontent.com/DruidMech/GameplayAbilitySystem_Aura/main/$rel" `
  -Headers @{'User-Agent'='claude'} -UseBasicParsing -OutFile $dest
Write-Output "SAVED: $dest"
```
→ 이후 `Read`로 `$dest`를 열어 참조. (스크래치패드 경로는 세션마다 다르니 시스템 프롬프트의
현재 스크래치패드 경로로 바꿔 쓴다.)

### B. 빌드 순서 / 도입 시점 조회 — 보조 수단
한 파일이 어떤 커밋들에서 만들어졌는지(강의가 그 기능을 어떤 순서로 가르쳤는지) 확인:
```powershell
$ProgressPreference='SilentlyContinue'
$rel = 'Source/Aura/Public/AbilitySystem/ExecCalc/ExecCalc_Damage.h'
Invoke-RestMethod "https://api.github.com/repos/DruidMech/GameplayAbilitySystem_Aura/commits?path=$rel&per_page=15" `
  -Headers @{'User-Agent'='claude'} |
  Select-Object @{n='date';e={$_.commit.author.date}}, @{n='msg';e={$_.commit.message.Split("`n")[0]}}
```
(비인증 GitHub API는 시간당 호출 제한이 있으니 남발하지 않는다.)

### C. (선택) 로컬 원격 추가 — 대량 대조가 필요할 때만
사용자가 원하면 완성본을 원격으로 붙여 오프라인 diff가 가능하다. 단, UE 저장소라 Content가
커서 받는 데 오래 걸릴 수 있으므로 **기본값은 A(원문 페치)** 로 하고 이건 선택지로만 안내한다.
```powershell
git remote add upstream https://github.com/DruidMech/GameplayAbilitySystem_Aura.git
git fetch upstream main --depth=1
# 이후: git show upstream/main:<경로> / 사용자 파일과 diff
```

## 커리큘럼 파트 ↔ 완성본 위치 지도
새 기능을 만들 때 아래 실제 파일을 정답지로 참고한다(이름은 완성본 기준 = 커리큘럼과 맞춤).

| 커리큘럼 | 완성본의 해당 코드(실명) |
|---|---|
| 2.2 Secondary/MMC | `AbilitySystem/ModMagCalc/MMC_MaxHealth.h`, `MMC_MaxMana.h` |
| 2.4 / 4.2 ExecCalc | `AbilitySystem/ExecCalc/ExecCalc_Damage.h` |
| 3.1 GA 베이스 | `AbilitySystem/Abilities/AuraGameplayAbility.h`, `AuraDamageGameplayAbility.h` |
| 3.2 입력 바인딩 | `Input/AuraInputConfig.h`, `AuraInputComponent.h` |
| 3.3 쿨다운 UI | `AbilitySystem/AsyncTasks/WaitCooldownChange.h` |
| 4.x 데미지/라이브러리 | `AbilitySystem/AuraAbilitySystemLibrary.h`, `AuraAbilitySystemGlobals.h` |
| 4.4 디버프 연출 | `AbilitySystem/Debuff/DebuffNiagaraComponent.h` |
| 5.1 투사체/타겟팅 | `AbilitySystem/Abilities/AuraProjectileSpell.h`, `AuraFireBolt.h`, `AbilityTasks/TargetDataUnderMouse.h`, `Actor/AuraProjectile.h` |
| 5.3 추가 스펠 | `Abilities/ArcaneShards.h`(AoE), `Electrocute.h`/`AuraBeamSpell.h`(빔), `AuraFireBlast.h` |
| 5.4 근접 | `Abilities/AuraMeleeAttack.h` |
| 6.x 적 AI | `AI/AuraAIController.h`, `BTService_FindNearestPlayer.h`, `BTTask_Attack.h`, `Abilities/AuraSummonAbility.h` |
| 7.x 성장/데이터 | `AbilitySystem/Data/LevelUpInfo.h`, `AttributeInfo.h`, `AbilityInfo.h`, `CharacterClassInfo.h` |
| 8.2/8.3 체크포인트 | `Checkpoint/Checkpoint.h`, `MapEntrance.h` |

**완성본에만 있는 추가 기능**(커리큘럼 기본 39스텝 밖): 패시브 어빌리티(`AuraPassiveAbility`,
`PassiveNiagaraComponent`), 소환(`AuraSummonAbility`), 캐릭터 클래스(`CharacterClassInfo`),
루트 등급(`LootTiers`). → 해당 파트에서 사용자가 원하면 곁가지로 얹거나, 완주 후 확장 과제로
다룬다. 진도 파일 메모에 결정을 남긴다.

## 정답지 사용 가드레일
- **점진 공개**: 완성본 파일은 *최종 상태*다(예: `AuraAttributeSet.h`가 이미 250여 줄로 모든
  Primary/Secondary 속성 포함). 초반 스텝에서 이 최종본을 통째로 붙여넣지 말 것. 튜터가
  참고하되, 지금 스텝에 해당하는 부분만 골라 보여준다.
- **미션 스포일 금지**: "직접 해보기" 정답을 사용자가 시도하기 전에 완성본에서 페치해
  미리 보여주지 않는다. 사용자가 시도/힌트요청/포기한 뒤에 정답지로 검증·해설한다.
- **이름은 완성본을 따른다**: 클래스/에셋 이름이 커리큘럼과 완성본이 다르면 완성본 이름을
  채택해 강의와 호환 유지. 채택한 이름을 진도 파일 메모에 기록.
- **가르치기 전 확인**: 완성본은 UE 5.5 기준이지만 세부가 바뀌었을 수 있다. 페치한 코드를
  그대로 신뢰하지 말고 현재 프로젝트에 맞는지 판단해 적용한다.
