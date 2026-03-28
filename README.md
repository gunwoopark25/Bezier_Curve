# Bezier Curve — De Casteljau Algorithm

C++17 구현체로, De Casteljau(드 카스텔조) 알고리즘을 사용해 임의 차수의 Bezier curve(베지어 곡선)를 계산하고 PostScript 파일로 시각화합니다.

---

## 프로젝트 개요

| 항목 | 내용 |
|------|------|
| 언어 | C++17 |
| 빌드 시스템 | CMake 3.20+ / Visual Studio (.vcxproj) |
| 외부 의존성 | 없음 (표준 라이브러리만 사용) |
| 입력 형식 | 제어점 좌표 텍스트 파일 |
| 출력 형식 | 좌표 텍스트 파일 + PostScript 시각화 파일 |

---

## 알고리즘 — De Casteljau

De Casteljau algorithm(드 카스텔조 알고리즘)은 Bezier curve를 수치적으로 안정적으로 계산하는 재귀적 선형 보간 방법입니다.

**핵심 수식:**

$$
P_i^{(r)}(t) = (1-t) \cdot P_i^{(r-1)} + t \cdot P_{i+1}^{(r-1)}, \quad r = 1, \ldots, n
$$

- $n$ : 곡선의 차수 (degree)
- $t \in [0, 1]$ : 곡선 매개변수
- $P_i^{(0)}$ : 원본 제어점 (control points)
- $P_0^{(n)}$ : 매개변수 $t$에서의 최종 곡선 좌표

알고리즘을 단계별로 도식화하면 다음과 같습니다 (3차 예시):

```
Level 0 (입력):   P0   P1   P2   P3
Level 1:           Q0   Q1   Q2
Level 2:            R0   R1
Level 3 (출력):      S0   ← t에서의 곡선 좌표
```

시간 복잡도는 $O(n^2)$, 공간 복잡도도 $O(n^2)$입니다.

---

## 폴더 구조

```
Bezier_Curve/
├── Bezier_Curve.slnx            # Visual Studio solution
├── README.md
└── Bezier_Curve/
    ├── CMakeLists.txt           # CMake 빌드 설정
    ├── main.cpp                 # 엔트리 포인트
    ├── De_Casteljau.h           # 클래스 선언
    ├── De_Casteljau.cpp         # 알고리즘 구현
    ├── degree2.txt              # 2차 테스트 입력 (제어점 3개)
    ├── degree3.txt              # 3차 테스트 입력 (제어점 4개)
    ├── degree4.txt              # 4차 테스트 입력 (제어점 5개)
    ├── degree5.txt              # 5차 테스트 입력 (제어점 6개)
    ├── degree6.txt              # 6차 테스트 입력 (제어점 7개) ← 현재 기본값
    ├── degree32.txt             # 32차 고차 테스트 입력 (제어점 33개)
    ├── Coordinate_degree3.txt   # 출력: 계산된 곡선 좌표
    └── curve.ps                 # 출력: PostScript 시각화
```

---

## 실행 흐름

```
fileLoad()           → 입력 파일에서 제어점 읽기 및 메모리 초기화
    ↓
normalization()      → 좌표 정규화 (첫 점을 원점으로 평행이동 후 거리로 스케일링)
    ↓
calculate()          → De Casteljau 알고리즘으로 곡선 좌표 계산
    ↓
solveNormalization() → 정규화 역변환 (원래 좌표계로 복원)
    ↓
saveFile()           → 결과 텍스트 파일 및 PostScript 파일 저장
```

---

## 핵심 클래스 — `De_Casteljau`

### 주요 멤버 변수

| 변수 | 타입 | 설명 |
|------|------|------|
| `Degree` | `int` | 곡선의 차수 |
| `Control_Point` | `int` | 제어점 수 = Degree + 1 |
| `Control_Coordinate` | `double**` | 제어점 좌표 배열 [Control_Point][4] |
| `Coordinate` | `double**` | 중간 계산 작업 배열 [(n+1)(n+2)/2][4] |
| `Result` | `double**` | 최종 곡선 좌표 [parameter][4] |
| `parameter` | `int` | 샘플링 수 (기본값: 11) |

### 메서드

| 메서드 | 역할 |
|--------|------|
| `fileLoad()` | 입력 파일 파싱 및 동적 메모리 할당 |
| `normalization()` | 좌표 정규화 변환 |
| `calculate()` | De Casteljau 재귀 보간 핵심 루프 |
| `solveNormalization()` | 정규화 역변환 |
| `saveFile()` | 텍스트 및 PostScript 출력 |

---

## 입력 파일 형식

```
<degree>
<x1> <y1>
<x2> <y2>
...
```

예시 (`degree3.txt` — 3차 Bezier curve):

```
3
100 100
200 200
300 200
400 100
```

---

## 출력 파일 형식

**좌표 텍스트 (`Coordinate_degree3.txt`):**
계산된 곡선 위의 좌표들이 한 행에 하나씩 기록됩니다.

```
100 100
...
400 100
```

**PostScript 시각화 (`curve.ps`):**
- 계산된 곡선 (연결된 선분)
- 제어점 (원으로 표시)
- 제어 다각형 (제어점 연결선)

---

## 빌드 방법

### CMake

```bash
mkdir build && cd build
cmake ..
cmake --build .
```

### Visual Studio

`Bezier_Curve.slnx`를 Visual Studio에서 열고 빌드합니다. x64/x86 구성 모두 지원됩니다.

---

## 입력 파일 변경

`De_Casteljau.cpp`의 `fileLoad()` 내부에서 파일명이 하드코딩되어 있습니다. 다른 차수의 테스트 케이스를 사용하려면 해당 파일명을 수정하세요.

```cpp
// De_Casteljau.cpp 내 fileLoad() — 파일명 수정
inFile.open("degree3.txt");  // 원하는 파일명으로 변경
```

---

## 참고 문헌

- Farin, G. (2002). *Curves and Surfaces for CAGD: A Practical Guide* (5th ed.). Morgan Kaufmann. — De Casteljau 알고리즘의 표준 교재
- de Casteljau, P. (1959). Outillages méthodes calcul. André Citroën Automobiles SA, Paris. — 원 알고리즘 제안 문서
- Piegl, L., & Tiller, W. (1997). *The NURBS Book* (2nd ed.). Springer. [DOI: 10.1007/978-3-642-97385-7](https://doi.org/10.1007/978-3-642-97385-7) — Bezier/NURBS 이론의 핵심 참고서
