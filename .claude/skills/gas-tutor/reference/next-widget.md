# "다음" 진행 위젯 규약

모든 스텝 마무리(그리고 세션 시작 안내)에서 아래 ①②를 **둘 다** 출력한다.
① show_widget 버튼 위젯 ② 텍스트 폴백 — 위젯이 렌더되지 않는 환경 대비.

## 준비
세션에서 처음 위젯을 쓰기 전에 `mcp__visualize__read_me`(modules: ["interactive"])를 조용히
호출한다(학습자에게 언급하지 않는다). read_me가 안내하는 CSS 변수를 우선 사용하고, 아래
템플릿의 변수명과 다르면 그에 맞춘다. 0.1 스텝의 개념 다이어그램을 그릴 때는 "diagram"
모듈도 함께 로드하면 된다.

## 위젯 스펙 (mcp__visualize__show_widget, HTML)
- title: `gas_tutor_next_step_<다음 스텝ID>` — 예: `gas_tutor_next_step_1_4`
- loading_messages: 한국어 1개(예: "다음 단계 버튼 준비 중")
- 구성:
  1. 방금 완료한 스텝 요약 1줄 — `✅ [스텝ID] [제목] 완료`
  2. 진행바 + `N/39 스텝 · Part K — 파트명` (N = 진도 파일의 완료 체크 수)
  3. 큰 버튼 — 라벨 `다음 ▶ [다음 스텝ID] [다음 스텝 제목]`, 클릭 시 `sendPrompt('다음')`
- 세션 시작 변형: 1번을 `이어서: 현재 위치` 안내로, 버튼 라벨을 `시작 ▶ …`으로 바꾼다.
- 배경 투명, 최상위 패딩 없음, 색은 CSS 변수(+폴백값) 사용.

### 템플릿 (텍스트만 치환해서 사용)
```html
<div style="max-width:560px;color:var(--text-primary,#ddd)">
  <div style="font-size:13px;opacity:.8;margin-bottom:8px">✅ <b>[1.3] AuraAttributeSet — 속성·복제·클램핑</b> 완료</div>
  <div style="height:8px;border-radius:4px;background:var(--border,rgba(127,127,127,.25));overflow:hidden">
    <div style="height:100%;width:13%;background:var(--accent,#6c9ef8)"></div>
  </div>
  <div style="font-size:12px;opacity:.65;margin:4px 0 12px">5/39 스텝 · Part 1 — 기존 코드 해부</div>
  <button onclick="sendPrompt('다음')" style="width:100%;padding:12px 16px;border-radius:10px;
    border:1.5px solid var(--accent,#6c9ef8);background:transparent;color:var(--accent,#6c9ef8);
    font-size:15px;font-weight:700;cursor:pointer;text-align:left">
    다음 ▶ <span style="font-weight:500">[1.4] 커스텀 ASC — EffectAssetTags 브로드캐스트</span>
  </button>
</div>
```

## 텍스트 폴백 (위젯 아래에 항상 함께 출력)
> ✅ 완료: 1.3 AuraAttributeSet · 진행 5/39
> **다음 ▶ 1.4 커스텀 ASC — EffectAssetTags 브로드캐스트**
> 준비되면 "다음"이라고 입력하세요. ("복습", "1.2로 돌아가자", "질문 있어"도 언제든 가능)

## 진행률 계산
전체 39스텝 기준. 진도 파일 체크리스트의 `[x]` 개수를 센다. 진행바 width % = 완료 수/39×100
(정수 반올림).
