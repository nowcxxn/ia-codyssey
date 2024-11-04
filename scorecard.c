#include <stdio.h>
#include <stdlib.h>

#define NUM_CANDIDATES 6
#define NUM_FIELDS 5
#define NUM_JUDGES 5
#define MAX_SCORE 100
#define MIN_SCORE 10

// 후보자 구조체 정의
typedef struct {
    char name[50];
    int id;
    int scores[NUM_FIELDS]; // 음악 소양, 댄스, 보컬, 비주얼, 전달력 점수
    int totalScore;
} Candidate;

// 심사자 구조체 정의
typedef struct {
    char name[50];
    char specialty[20]; // 심사자 전문 분야 (음악, 댄스 등)
} Judge;

// 후보자 초기화
Candidate candidates[NUM_CANDIDATES] = {
    {"박지연", 123456, {0, 0, 0, 0, 0}, 0},
    {"Ethan Smith", 234567, {0, 0, 0, 0, 0}, 0},
    {"Suphanan Wong", 345678, {0, 0, 0, 0, 0}, 0},
    {"Helena Silva", 456789, {0, 0, 0, 0, 0}, 0},
    {"Karolina Nowak", 567890, {0, 0, 0, 0, 0}, 0},
    {"Liam Wilson", 678901, {0, 0, 0, 0, 0}, 0}
};

// 심사자 초기화
Judge judges[NUM_JUDGES] = {
    {"김영수", "음악"},
    {"이지영", "댄스"},
    {"박민준", "보컬"},
    {"송현우", "비주얼"},
    {"박지영", "전달력"}
};

// 평가 시트 배열
int scoring_sheet[NUM_CANDIDATES][7]; // 후보자 고유 ID, 5개 분야 점수, 총점

// 평가 시트 초기화
void initializeScoringSheet() {
    for (int i = 0; i < NUM_CANDIDATES; i++) {
        scoring_sheet[i][0] = candidates[i].id; // 후보자 고유 ID 저장
        for (int j = 1; j <= NUM_FIELDS; j++) {
            scoring_sheet[i][j] = 0; // 점수 초기화
        }
        scoring_sheet[i][6] = 0; // 총점 초기화
    }
}

// 점수 입력 받는 함수
void inputScores() {
    for (int i = 0; i < NUM_JUDGES; i++) {
        printf("####################################\n");
        printf("#       오디션 심사 결과 입력      #\n");
        printf("####################################\n");
        printf("> 심사자 이름: %s\n", judges[i].name);
        printf("> 전문 분야: %s\n", judges[i].specialty);
        printf("++++++++++++++++++++++++++++++++++++\n");

        for (int j = 0; j < NUM_CANDIDATES; j++) {
            int score;
            do {
                printf("후보자: %s\n", candidates[j].name);
                printf("%s : ", judges[i].specialty);
                scanf("%d", &score);
                if (score < MIN_SCORE || score > MAX_SCORE) {
                    printf("유효하지 않은 점수입니다. 10점에서 100점 사이로 입력해주세요.\n");
                }
            } while (score < MIN_SCORE || score > MAX_SCORE);

            // 점수를 저장 (scoring_sheet에 기록)
            scoring_sheet[j][i + 1] = score;
            printf("------------------------------------\n");
        }
    }
}

// 총점 계산 함수
void calculateTotalScores() {
    for (int i = 0; i < NUM_CANDIDATES; i++) {
        scoring_sheet[i][6] = 0; // 총점 초기화
        for (int j = 1; j <= NUM_FIELDS; j++) {
            scoring_sheet[i][6] += scoring_sheet[i][j]; // 총점 누적
        }
    }
}

// 후보자들을 점수 순으로 정렬
void sortCandidates() {
    for (int i = 0; i < NUM_CANDIDATES - 1; i++) {
        for (int j = i + 1; j < NUM_CANDIDATES; j++) {
            if (scoring_sheet[i][6] < scoring_sheet[j][6]) {
                int temp[7];
                for (int k = 0; k < 7; k++) {
                    temp[k] = scoring_sheet[i][k];
                    scoring_sheet[i][k] = scoring_sheet[j][k];
                    scoring_sheet[j][k] = temp[k];
                }
            }
        }
    }
}

// 모든 후보자 점수 출력
void reviewScores() {
    printf("입력을 모두 완료했습니다.\n");
    printf("입력하신 내용을 검토하세요!\n");
    printf("------------------------------------\n");

    for (int i = 0; i < 6; i++) { // 상위 4명 출력
        for (int j = 0; j < NUM_CANDIDATES; j++) {
            if (scoring_sheet[j][0] == candidates[i].id) {
                printf("%d. %s (%d점)\n", i + 1, candidates[i].name, scoring_sheet[j][6]);
            }
        }
    }
}

// 제출 여부 확인
char confirmSubmission() {
    char confirmation;
    printf("제출하시겠습니까? (Y/N): ");
    scanf(" %c", &confirmation); // 이전 입력에서 개행 문자가 남아있을 수 있으므로 앞에 공백 추가
    return confirmation;
}

// 결과 출력
void printResults() {
    printf("\n=======================================\n");
    printf("후보 선발 결과 집계 중 ...\n");
    printf("=======================================\n");
    printf("#######################################\n");
    printf("# 밀리웨이즈의 멤버가 된 걸축하합니다!  #\n");
    printf("#######################################\n");

    // 상위 4명 출력
    for (int i = 0; i < 4; i++) { // 4명만 출력
        printf("%d. ", i + 1); // 순위 출력
        for (int j = 0; j < NUM_CANDIDATES; j++) {
            if (scoring_sheet[i][0] == candidates[j].id) { // 정렬된 점수에 맞는 후보자 찾기
                printf("%s (%d점)\n", candidates[j].name, scoring_sheet[i][6]); // 이름과 점수 출력
                break; // 찾으면 더 이상 반복하지 않음
            }
        }
    }
}

// 프로그램 실행 함수
void runProgram() {
    while (1) { // 무한 루프를 통해 반복 입력 가능
        initializeScoringSheet(); // 평가 시트 초기화
        inputScores();  // 점수 입력
        calculateTotalScores(); // 총점 계산
        sortCandidates(); // 후보자 정렬
        
        reviewScores(); // 점수 검토
        char confirmation = confirmSubmission(); // 제출 여부 확인
        
        if (confirmation == 'Y' || confirmation == 'y') {
            printf("***최종 제출을 완료했습니다.***\n");
            printResults();  // 결과 출력
            break; // 프로그램 종료
        } else {
            printf("다시 입력을 시작합니다.\n");
        }
    }
}

int main() {
    runProgram();
    return 0;
}