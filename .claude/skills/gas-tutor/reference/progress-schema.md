# 진도 파일 스키마 — docs/gas-progress.md

튜터가 첫 실행 시 아래 템플릿 그대로 생성하고, 스텝이 끝날 때마다 갱신한다. 학습자가 직접
수정할 수도 있으므로 **세션 시작 시 항상 파일의 현재 내용을 진실로 삼는다.**

## 생성 규칙
- 아래 템플릿을 그대로 복사해 생성한다(체크리스트는 curriculum.md와 동일한 ID·제목).
- 엔진 경로는 build-and-run.md 절차로 확보되는 즉시 기록한다.
- 날짜는 오늘 날짜(YYYY-MM-DD)로.

## 템플릿

```markdown
# GAS 학습 진도 — /gas-tutor

> 이 파일은 gas-tutor 튜터가 관리합니다. 직접 수정해도 됩니다(다음 세션에 반영됩니다).

## 설정
- 엔진 경로: (미확인)
- 프로젝트: E:\UE5_PortfolioPrj\Aura\Aura.uproject
- 마지막 업데이트: YYYY-MM-DD

## 현재 스텝
**0.1 — GAS 전체 그림** (다음에 할 일: 학습목표부터 시작)

## 체크리스트
### Part 0 — 오리엔테이션 & 큰 그림
- [ ] 0.1 GAS 전체 그림
- [ ] 0.2 프로젝트 투어 & 빌드 워크플로우
### Part 1 — 기존 코드 해부
- [ ] 1.1 캐릭터 계층과 ASC 소유권
- [ ] 1.2 InitAbilityActorInfo — ASC 초기화 타이밍
- [ ] 1.3 AuraAttributeSet — 속성·복제·클램핑
- [ ] 1.4 커스텀 ASC — EffectAssetTags 브로드캐스트
- [ ] 1.5 AuraEffectActor — GE 적용/제거 정책
- [ ] 1.6 WidgetController UI 아키텍처
- [ ] 1.7 Enhanced Input & CursorTrace 하이라이트
- [ ] 1.8 GameplayTag 등록과 메시지 DataTable
### Part 2 — 속성 확장 & GE 심화
- [ ] 2.1 Primary 속성 4종
- [ ] 2.2 Secondary 파생 속성 + MMC
- [ ] 2.3 기본값 초기화 파이프라인
- [ ] 2.4 Modifier/MMC/ExecCalc 선택 기준
### Part 3 — GameplayAbility 기초
- [ ] 3.1 UAuraGameplayAbility와 어빌리티 부여
- [ ] 3.2 InputTag 기반 입력 바인딩
- [ ] 3.3 Cost & Cooldown
- [ ] 3.4 어빌리티 라이프사이클 & 예측 개요
### Part 4 — 전투와 데미지
- [ ] 4.1 Damage 메타 속성과 PostGameplayEffectExecute
- [ ] 4.2 ExecCalc_Damage 데미지 공식
- [ ] 4.3 SetByCaller와 레벨 스케일링
- [ ] 4.4 HitReact와 사망 연출
### Part 5 — 어빌리티 구현
- [ ] 5.1 AuraProjectile + FireBolt
- [ ] 5.2 GameplayCue 임팩트 연출
- [ ] 5.3 (심화 실습) 두 번째 스펠 — AoE
- [ ] 5.4 근접 공격
### Part 6 — 적 AI
- [ ] 6.1 AuraAIController + Behavior Tree
- [ ] 6.2 적의 어빌리티 사용
- [ ] 6.3 적 체력바와 레벨별 스탯
### Part 7 — 성장 시스템 & 메뉴 UI
- [ ] 7.1 경험치 파이프라인
- [ ] 7.2 레벨업
- [ ] 7.3 속성 메뉴 (AttributeMenu)
- [ ] 7.4 스펠 메뉴와 장착
### Part 8 — 게임 완성과 배포
- [ ] 8.1 메인 메뉴와 게임 플로우
- [ ] 8.2 세이브 & 로드
- [ ] 8.3 레벨 구성 — 플레이 가능한 던전
- [ ] 8.4 사운드·폴리시·밸런싱
- [ ] 8.5 Windows Shipping 패키징
- [ ] 8.6 배포와 포트폴리오

## 메모
- (막힌 점, 커스터마이즈 결정, 추가 질문거리를 날짜와 함께 한 줄씩 누적)
```

## 갱신 규칙
- **스텝 완료 시점** = 직접 해보기 해설까지 끝났을 때. 해당 항목을 `[x]`로, 현재 스텝
  포인터를 다음 스텝으로, 마지막 업데이트 날짜를 오늘로 갱신한다.
- 스텝 중간에 세션이 끊길 수 있다. 큰 하위 작업(빌드 성공, 에셋 완성, 미션 제시 등)이
  끝나면 현재 스텝 줄의 `(다음에 할 일: …)` 메모를 갱신해 두면 재개가 매끄럽다.
- **점프/복습**: 현재 스텝 포인터만 이동하고 완료 체크는 유지한다. 메모에 사유 한 줄.
- **메모**: 학습자가 막혔던 지점, 이름을 다르게 지은 것(커스터마이즈), 나중에 다루기로 한
  질문을 짧게 누적한다. 다음 세션의 튜터가 읽고 이어간다.
- 완주(8.6) 시: 파일 상단에 `🎉 수료: YYYY-MM-DD`를 추가한다.
