# 빌드 · 에디터 실행 · 로그 규약

- 프로젝트: `E:\UE5_PortfolioPrj\Aura\Aura.uproject` (UE 5.5, 에디터 타겟 `AuraEditor`)
- 명령은 PowerShell 도구로 실행한다. PowerShell 5.1 문법 주의(`&&`·삼항 연산자 없음,
  순차 실행은 `;`).

## 1) 엔진 경로 확보 (세션당 1회)
우선순위대로 시도하고, 확정되면 `docs/gas-progress.md` 설정 블록에 저장한다.

1. 진도 파일 설정 블록에 저장된 경로 → `Test-Path`로 재검증 후 사용.
2. 런처 설치 레지스트리:
   ```powershell
   (Get-ItemProperty 'HKLM:\SOFTWARE\EpicGames\Unreal Engine\5.5' -ErrorAction Stop).InstalledDirectory
   ```
3. 소스 빌드 등록: `HKCU:\SOFTWARE\Epic Games\Unreal Engine\Builds`의 값들 확인.
4. 관례 경로: `C:\Program Files\Epic Games\UE_5.5`
5. 전부 실패 → AskUserQuestion으로 1회만 질문.

최종 검증: `Test-Path "<엔진>\Engine\Build\BatchFiles\Build.bat"`가 True여야 확정.

## 2) C++ 빌드 (에디터 타겟)
**빌드 전에 에디터가 닫혀 있는지 사용자에게 확인**한다. 에디터가 모듈 DLL을 잡고 있으면
링크가 실패하거나 Live Coding과 충돌한다. (이 커리큘럼의 표준 사이클: 에디터 종료 → 빌드 →
에디터 재실행.)

```powershell
& "<엔진>\Engine\Build\BatchFiles\Build.bat" AuraEditor Win64 Development -Project="E:\UE5_PortfolioPrj\Aura\Aura.uproject" -WaitMutex -NoHotReload
```

- timeout 600000(10분)으로 실행. 전체 리빌드가 예상되면(첫 빌드, 엔진 업데이트 직후)
  run_in_background로 돌리고 완료 통지를 기다린다.
- 성공: exit code 0, 출력 끝에 `Total execution time`. 변경이 없으면 `Target is up to date`.
- 실패: 첫 에러 라인(`error C…`, `LNK…`)을 찾아 원인 분석 → 해당 파일 수정 → 재빌드.
  에러 원문 일부를 반드시 학습자에게 인용한다(얼버무리기 금지). 에러 자체가 학습 재료다.
- 자주 보는 에러: include 누락(C2065/C2039), 모듈 의존 누락(LNK2019 → `Aura.Build.cs` 확인),
  UHT 에러(UFUNCTION/UPROPERTY 문법), 에디터가 열려 있어 DLL 잠김.

## 3) 에디터 실행 (독립 프로세스로)
```powershell
Start-Process -FilePath "<엔진>\Engine\Binaries\Win64\UnrealEditor.exe" -ArgumentList '"E:\UE5_PortfolioPrj\Aura\Aura.uproject"'
```
- `Start-Process`라 즉시 리턴된다. 로딩에 1~3분(셰이더 컴파일 시 더) 걸린다고 안내한다.
- 실행 여부 확인: `Get-Process UnrealEditor -ErrorAction SilentlyContinue`

## 4) 로그 확인
- 현재 세션: `E:\UE5_PortfolioPrj\Aura\Saved\Logs\Aura.log` — 에디터 실행 중에도 Read/Grep 가능.
- 이전 세션: `Saved\Logs\Aura-backup-*.log` (파일명에 타임스탬프).
- PIE 테스트 루틴:
  1. 학습자에게 Play(툴바 ▶ 또는 Alt+P)와 관찰 포인트를 안내
  2. 학습자가 본 것을 보고받고
  3. 튜터가 로그에서 예상 라인을 Grep으로 확인(커스텀 UE_LOG 카테고리 권장)
  4. 화면에서 바로 볼 값은 `GEngine->AddOnScreenDebugMessage` 활용.
- PIE 자체는 CLI로 자동화하지 않는다(항상 학습자가 직접 재생).

## 5) 패키징 (Part 8.5에서 사용)
```powershell
& "<엔진>\Engine\Build\BatchFiles\RunUAT.bat" BuildCookRun -project="E:\UE5_PortfolioPrj\Aura\Aura.uproject" -platform=Win64 -clientconfig=Shipping -build -cook -stage -pak -archive -archivedirectory="E:\UE5_PortfolioPrj\Aura\Packaged" -nop4 -utf8output
```
- 수십 분 소요 → 반드시 run_in_background로 실행하고 완료 통지를 기다린다.
- 완료 후 `BUILD SUCCESSFUL` 문자열과 산출 폴더(`Packaged\Windows`)를 확인한다.
- 사전 조건: Project Settings → Maps & Modes의 Game Default Map, Packaging의 List of maps
  to include 지정(8.5 스텝에서 안내).
