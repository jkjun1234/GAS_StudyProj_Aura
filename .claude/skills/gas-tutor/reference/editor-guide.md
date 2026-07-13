# 에디터 작업 안내 규약 (클릭 단위 가이드)

.uasset(BP/GE/위젯/DataTable/커브/BT 등)은 바이너리 포맷이라 CLI·코드로 생성하지 않는다.
항상 아래 규칙대로 클릭 단위 절차를 안내하고, 완료 확인 후에 다음으로 넘어간다.

## 안내 작성 규칙
1. 에셋 하나당 절차 하나. 번호 목록으로, 한 항목 = 클릭 1~2회 분량.
2. 위치는 콘텐츠 브라우저 전체 경로로 쓴다 — 예: `Content/Blueprints/AbilitySystem/GE_HealthPotion`
3. 설정값은 표로 정리한다: | 항목(Details 패널 경로) | 값 | 비고 |
4. 끝에 항상 "컴파일 → 저장" + '이렇게 보이면 성공' 확인 포인트 1개를 붙인다.
5. 학습자가 막히면 스크린샷을 붙여 달라고 요청한다(이미지를 읽고 진단할 수 있다).
6. 에셋 이름 접두사 관례: `BP_`(액터) `GE_` `GA_` `WBP_`(위젯) `DT_` `CT_`(커브) `BT_` `BB_`
   `DA_`(데이터에셋) `GC_`(GameplayCue) `IA_`/`IMC_`(입력) `M_`/`MI_`(머티리얼)

## 공통 패턴 레시피

### 블루프린트 클래스
대상 폴더 우클릭 → Blueprint Class → All Classes 검색창에 부모 C++ 클래스명(예:
AuraEffectActor) → 선택 → 이름 입력 → 더블클릭으로 열기.

### GameplayEffect
부모 GameplayEffect로 BP 생성 → Details에서:
- Duration Policy: Instant / Has Duration / Infinite
- Modifiers 배열 + : Attribute / Modifier Op(Add·Multiply·Override) /
  Magnitude Calculation Type(Scalable Float · Attribute Based · Custom Calculation Class ·
  Set by Caller)

### GameplayTag 추가
Edit → Project Settings → Project → GameplayTags → Gameplay Tag List → Add New Tag.
(`Config/DefaultGameplayTags.ini`에 기록된다. ini를 직접 편집할 수도 있으나 에디터가 열려
있으면 재시작 필요. C++ 네이티브 태그 방식은 커리큘럼 후반에 별도로 다룬다.)

### DataTable
우클릭 → Miscellaneous → Data Table → 행 구조체 선택(예: UIWidgetRow,
GameplayTagTableRow) → 이름 `DT_*`. 행 추가는 상단 +Add 버튼.

### Curve Table
우클릭 → Miscellaneous → Curve Table → 행 추가 후 (레벨, 값) 키 입력. ScalableFloat에서
"커브테이블 에셋 + 행 이름"으로 참조.

### Input Action / Mapping Context (Enhanced Input)
우클릭 → Input → Input Action(`IA_*`, Value Type 주의: Digital/Axis1D/Axis2D) 또는
Input Mapping Context(`IMC_*`). IMC 안에서 IA별로 키 매핑과 Modifier(Swizzle/Negate 등) 추가.

### Widget Blueprint
우클릭 → User Interface → Widget Blueprint(`WBP_*`). 부모를 커스텀 C++ 위젯(AuraUserWidget
계열)으로 바꾸려면: 위젯 에디터 툴바 Class Settings → Details → Parent Class 변경.

### Behavior Tree / Blackboard
우클릭 → Artificial Intelligence → Behavior Tree / Blackboard. BT 에디터 Details에서
Blackboard Asset 연결. Blackboard 키는 +New Key.

### Blueprint 그래프 안내
노드 추가는 "그래프 우클릭 → 검색어" 형식으로 안내한다 — 예: 그래프 우클릭 →
"Apply Gameplay Effect Spec To Self" 검색. 핀 연결은 순서 목록이나 표로 명시하고,
그래프가 복잡하면 단계를 나눠 중간 확인을 받는다.

## 완료 확인 방법 (하나 이상 사용)
- 학습자의 확인("됐어요") + 핵심 설정 스크린샷(권장)
- PIE 동작 결과(예: 메시지 위젯 출력, 하이라이트 동작)
- 로그 확인(`Saved/Logs`) — 로드 에러/워닝 없는지, 커스텀 로그가 찍히는지
- C++에서 참조하는 에셋이면 다음 실행에서 nullptr 관련 워닝이 없는지
