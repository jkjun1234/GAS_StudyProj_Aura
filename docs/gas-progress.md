# GAS 학습 진도 — /gas-tutor

> 이 파일은 gas-tutor 튜터가 관리합니다. 직접 수정해도 됩니다(다음 세션에 반영됩니다).

## 설정
- 엔진 경로: C:\Program Files\Epic Games\UE_5.5
- 프로젝트: E:\UE5_PortfolioPrj\Aura\Aura.uproject
- 마지막 업데이트: 2026-07-14

## 현재 스텝
**1.1 — 캐릭터 계층과 ASC 소유권** (다음에 할 일: 학습목표부터 처음 진행 — 지난 세션 설명 도중 중단됨)

## 체크리스트
### Part 0 — 오리엔테이션 & 큰 그림
- [ ] 0.1 GAS 전체 그림  (건너뜀: 사용자 선택 1번 — 원하면 나중에 복습)
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
- 2026-07-07 진도 파일 최초 생성.
- 2026-07-14 재개. 사용자 선택 "1번 = 기존 코드 해부(Part 1)부터 복습". 원본 강의
  섹션 1~6 + 섹션7 lecture 58까지 완료 → 강의 59번 이후가 미시청 신규 구간.
  엔진 경로 확인 완료(레지스트리). Step 1.1 도입부 설명 중 사용자가 중단 —
  실제 수업은 새 세션에서 /gas-tutor로 시작 예정. 1.1을 처음부터 진행할 것.
