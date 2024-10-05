#include <stdio.h>
#include <stdlib.h>

// 후보자의 속성 정보 배열 (순서: 이름, 생일, 성별, 메일, 국적, BMI, 주 스킬, 보조 스킬, 한국어 등급(TOPIK), MBTI, 자기소개)
char* member_info[] = { "이름", "생일(YYYY/MM/DD 형식)", "성별(여성이면 F 또는 남성이면 M)", "메일 주소", "국적", "BMI", "주 스킬", "보조 스킬", "한국어 등급(TOPIK)", "MBTI", "자기소개" };

// 후보자 6명의 데이터를 저장할 배열 (각각의 후보자를 위한 배열)
char candidate01[11][100], candidate02[11][100], candidate03[11][100], candidate04[11][100], candidate05[11][100], candidate06[11][100];

// 나이 계산 함수 (생일로부터 만 나이를 계산)
int calculate_age(const char* birthdate) {
    int year, month, day;
    sscanf_s(birthdate, "%d/%d/%d", &year, &month, &day);

    int current_year = 2024, current_month = 10, current_day = 5;
    int age = current_year - year;

    if (current_month < month || (current_month == month && current_day < day)) {
        age--; // 아직 생일이 지나지 않은 경우 나이를 한 살 줄임
    }

    return age;
}

// 개행 문자 제거 함수
void remove_newline(char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '\n') {
            str[i] = '\0'; // '\n' 문자를 null 문자로 대체
            break;
        }
    }
}

// 성별 변환 함수
const char* convert_gender(const char* gender) {
    if (gender[0] == 'F' || gender[0] == 'f') {
        return "여자";
    }
    else if (gender[0] == 'M' || gender[0] == 'm') {
        return "남자";
    }
    else {
        return "미상"; // 잘못된 입력 처리
    }
}

void print_all_candidates_data(char* candidates[6][11], char* group_name) {
    printf("\n####################################\n");
    printf("[%s] 오디션 후보자 전체 데이터 조회\n", group_name);
    printf("####################################\n");
    printf("==============================================================================================\n");
    printf("성   명    | 생  일 | 성별 | 메  일             | 국적  | BMI | 주 스킬 | 보조 스킬 | TOPIK | MBTI \n");
    printf("==============================================================================================\n");

    for (int i = 0; i < 6; i++) {
        if (candidates[i][0][0] != '\0') { // 후보자 정보가 입력되었는지 확인
            int age = calculate_age(candidates[i][1]);

            // 생일 포맷을 YYYYMMDD로 변경
            char formatted_birthdate[9]; // 8자 + null terminator
            snprintf(formatted_birthdate, sizeof(formatted_birthdate), "%c%c%c%c%c%c%c%c",
                candidates[i][1][0], candidates[i][1][1], candidates[i][1][2], candidates[i][1][3], // YYYY
                candidates[i][1][5], candidates[i][1][6], // MM
                candidates[i][1][8], candidates[i][1][9]); // DD
            formatted_birthdate[8] = '\0'; // null terminator 추가

            printf("%s(%d) | %s | %s  | %s | %s | %s | %s | %s | 원어민 | %s\n",
                candidates[i][0], age, formatted_birthdate, convert_gender(candidates[i][2]), candidates[i][3],
                candidates[i][4], candidates[i][5], candidates[i][6], candidates[i][7], candidates[i][9]);
        
            // 자기소개 출력
            printf("        -------------------------------------------------------------------------------------\n");
            printf("%s\n", candidates[i][10]); // 자기소개 출력
            printf("---------------------------------------------------------------------------------------------\n");
        }
    }

    printf("==============================================================================================\n");
}

int main() {
    // 그룹명 입력 받기
    char group_name[50];
    char ch;
    int i = 0;

    printf("오디션 그룹명을 입력하세요: ");
    while ((ch = getchar()) != '\n' && i < sizeof(group_name) - 1) { // '\n'이 입력될 때까지 읽음
        group_name[i++] = ch; // 문자를 저장
    }
    group_name[i] = '\0'; // null terminator 추가

    // 후보자 데이터를 저장할 배열들의 포인터 배열
    char* candidates[6][11] = {
        {candidate01[0], candidate01[1], candidate01[2], candidate01[3], candidate01[4], candidate01[5], candidate01[6], candidate01[7], candidate01[8], candidate01[9], candidate01[10]},
        {candidate02[0], candidate02[1], candidate02[2], candidate02[3], candidate02[4], candidate02[5], candidate02[6], candidate02[7], candidate02[8], candidate02[9], candidate02[10]},
        {candidate03[0], candidate03[1], candidate03[2], candidate03[3], candidate03[4], candidate03[5], candidate03[6], candidate03[7], candidate03[8], candidate03[9], candidate03[10]},
        {candidate04[0], candidate04[1], candidate04[2], candidate04[3], candidate04[4], candidate04[5], candidate04[6], candidate04[7], candidate04[8], candidate04[9], candidate04[10]},
        {candidate05[0], candidate05[1], candidate05[2], candidate05[3], candidate05[4], candidate05[5], candidate05[6], candidate05[7], candidate05[8], candidate05[9], candidate05[10]},
        {candidate06[0], candidate06[1], candidate06[2], candidate06[3], candidate06[4], candidate06[5], candidate06[6], candidate06[7], candidate06[8], candidate06[9], candidate06[10]}
    };

    // 후보자 정보 입력
    for (int i = 0; i < 6; i++) {
        if (i == 0) {
            // 첫 번째 후보자일 때 출력
            printf("\n####################################\n");
            printf("[%s] 오디션 후보자 데이터 입력\n", group_name);
            printf("####################################\n");
            printf("첫 번째 후보자의 정보를 입력합니다.\n");
            printf("---------------------------------\n");
        }
        else {
            // 두 번째 이후 후보자일 때 출력
            printf("\n=================================\n");
            printf("%s 후보자를 입력합니다.\n", (i == 1) ? "두 번째" : (i == 2) ? "세 번째" : (i == 3) ? "네 번째" : (i == 4) ? "다섯 번째" : "여섯 번째");
            printf("---------------------------------\n");
        }

        // 후보자의 정보 입력
        for (int j = 0; j < 11; j++) {
            printf("%d. %s: ", j + 1, member_info[j]);  // 각 입력 앞에 번호 추가
            fgets(candidates[i][j], 100, stdin);
            remove_newline(candidates[i][j]);  // 개행 문자 제거
        }
    }

    // 모든 후보자 정보를 입력한 후에 전체 후보자 데이터 출력
    print_all_candidates_data(candidates, group_name);

    return 0;
}
