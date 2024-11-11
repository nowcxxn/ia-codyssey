#include <stdio.h>
#include <math.h>

// 상수 정의
#define TOTAL_FIELDS 9
#define MAX_ROOMS 10
#define MIN_DAYS 30
#define MAX_DAYS 100

// 시험 분야 배열
const char *fields[TOTAL_FIELDS] = {
    "체력", "지식", "자기관리", "팀워크", "한국어", "보컬", "댄스", "비주얼", "연기"
};

// 시험 일정 구조
int exam_dates[TOTAL_FIELDS] = {0};  // 각 분야의 시험 일정을 저장

// 유틸리티 함수
int calculate_days(int start_date, int end_date) {
    int start_year = start_date / 10000;
    int start_month = (start_date / 100) % 100;
    int start_day = start_date % 100;

    int end_year = end_date / 10000;
    int end_month = (end_date / 100) % 100;
    int end_day = end_date % 100;

    return abs((end_year - start_year) * 365 + (end_month - start_month) * 30 + (end_day - start_day));
}

int is_valid_exam_date(int start_date, int exam_date) {
    int days = calculate_days(start_date, exam_date);
    return (days >= MIN_DAYS && days <= MAX_DAYS);
}

void display_exam_schedule(int start_date) {
    printf("\n--- 시험 일정 ---\n");
    int has_scheduled_exams = 0; // 시험 일정이 있는지 여부를 확인하기 위한 변수
    for (int i = 0; i < TOTAL_FIELDS; i++) {
        if (exam_dates[i] != 0) {
            printf("분야: %s, 시험 날짜: %d\n", fields[i], exam_dates[i]);
            has_scheduled_exams = 1; // 최소한 하나의 시험 일정이 출력됨
        }
    }
    if (!has_scheduled_exams) {
        printf("예약된 시험 일정이 없습니다.\n"); // 예약된 시험 일정이 없을 경우 출력
    }
}

// 체력과 지식 인증 확인 함수
int check_passed_certification(int field_index) {
    if (exam_dates[field_index] == 0) {
        printf("%s 인증을 진행했습니까? (예: 1 / 아니오: 0): ", fields[field_index]);
        int passed;
        scanf("%d", &passed);
        if (passed == 0) {
            printf("%s 인증을 완료한 후 다시 시도하세요.\n", fields[field_index]);
            return 0;
        } else {
            printf("%s 인증이 완료되었습니다.\n", fields[field_index]);
            // 인증 완료 여부만 확인하고 일정에는 추가하지 않음
        }
    }
    return 1;
}

// 메인 프로그램
int main() {
    int start_date;
    int current_date;
    
    printf("훈련 시작 날짜를 입력하세요 (YYYYMMDD): ");
    scanf("%d", &start_date);
    
    printf("현재 날짜를 입력하세요 (YYYYMMDD): ");
    scanf("%d", &current_date);

    int choice, exam_date;
    while (1) {
        printf("\n시험 분야를 선택하세요:\n");
        for (int i = 0; i < TOTAL_FIELDS; i++) {
            printf("%d. %s\n", i + 1, fields[i]);
        }
        printf("0을 입력하면 일정 확인을 위해 종료합니다.\n");
        scanf("%d", &choice);

        if (choice == 0) {
            break;
        } else if (choice < 1 || choice > TOTAL_FIELDS) {
            printf("잘못된 선택입니다. 다시 시도하세요.\n");
            continue;
        }
        
        choice -= 1;  // 0부터 시작하는 인덱스로 조정

        // 체력과 지식 인증 여부 확인
        if (choice > 1) {
            if (!check_passed_certification(0) || !check_passed_certification(1)) {
                continue;
            }
        }

        printf("%s의 시험 날짜를 입력하세요 (YYYYMMDD): ", fields[choice]);
        scanf("%d", &exam_date);

        // 훈련 시작 날짜 기준으로 시험 날짜의 유효성을 확인
        if (is_valid_exam_date(start_date, exam_date)) {
            exam_dates[choice] = exam_date;
            printf("%s 분야의 시험이 %d에 예약되었습니다.\n", fields[choice], exam_date);
        } else {
            printf("유효하지 않은 날짜입니다. 시험은 시작 날짜로부터 %d일에서 %d일 사이에 있어야 합니다.\n", MIN_DAYS, MAX_DAYS);
        }
    }

    display_exam_schedule(start_date);

    // 보너스: 리마인더 및 방 배정
    printf("\n--- 리마인더 및 방 배정 ---\n");
    for (int i = 0; i < TOTAL_FIELDS; i++) {
        if (exam_dates[i] != 0) {
            int days_to_exam = calculate_days(current_date, exam_dates[i]);

            if (days_to_exam == 0) {
                printf("오늘은 %s 분야의 시험 날입니다. 배정된 방: %d\n", fields[i], (current_date % MAX_ROOMS) + 1);
            } else if (days_to_exam <= 10) {
                printf("알림: %s 분야 시험이 %d일 후 %d에 예정되어 있습니다.\n", fields[i], days_to_exam, exam_dates[i]);
            }
        }
    }

    return 0;
}
