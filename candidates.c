#include <stdio.h>
#include <stdlib.h>

// �ĺ����� �Ӽ� ���� �迭 (����: �̸�, ����, ����, ����, ����, BMI, �� ��ų, ���� ��ų, �ѱ��� ���(TOPIK), MBTI, �ڱ�Ұ�)
char* member_info[] = { "�̸�", "����(YYYY/MM/DD ����)", "����(�����̸� F �Ǵ� �����̸� M)", "���� �ּ�", "����", "BMI", "�� ��ų", "���� ��ų", "�ѱ��� ���(TOPIK)", "MBTI", "�ڱ�Ұ�" };

// �ĺ��� 6���� �����͸� ������ �迭 (������ �ĺ��ڸ� ���� �迭)
char candidate01[11][100], candidate02[11][100], candidate03[11][100], candidate04[11][100], candidate05[11][100], candidate06[11][100];

// ���� ��� �Լ� (���Ϸκ��� �� ���̸� ���)
int calculate_age(const char* birthdate) {
    int year, month, day;
    sscanf_s(birthdate, "%d/%d/%d", &year, &month, &day);

    int current_year = 2024, current_month = 10, current_day = 5;
    int age = current_year - year;

    if (current_month < month || (current_month == month && current_day < day)) {
        age--; // ���� ������ ������ ���� ��� ���̸� �� �� ����
    }

    return age;
}

// ���� ���� ���� �Լ�
void remove_newline(char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '\n') {
            str[i] = '\0'; // '\n' ���ڸ� null ���ڷ� ��ü
            break;
        }
    }
}

// ���� ��ȯ �Լ�
const char* convert_gender(const char* gender) {
    if (gender[0] == 'F' || gender[0] == 'f') {
        return "����";
    }
    else if (gender[0] == 'M' || gender[0] == 'm') {
        return "����";
    }
    else {
        return "�̻�"; // �߸��� �Է� ó��
    }
}

void print_all_candidates_data(char* candidates[6][11], char* group_name) {
    printf("\n####################################\n");
    printf("[%s] ����� �ĺ��� ��ü ������ ��ȸ\n", group_name);
    printf("####################################\n");
    printf("==============================================================================================\n");
    printf("��   ��    | ��  �� | ���� | ��  ��             | ����  | BMI | �� ��ų | ���� ��ų | TOPIK | MBTI \n");
    printf("==============================================================================================\n");

    for (int i = 0; i < 6; i++) {
        if (candidates[i][0][0] != '\0') { // �ĺ��� ������ �ԷµǾ����� Ȯ��
            int age = calculate_age(candidates[i][1]);

            // ���� ������ YYYYMMDD�� ����
            char formatted_birthdate[9]; // 8�� + null terminator
            snprintf(formatted_birthdate, sizeof(formatted_birthdate), "%c%c%c%c%c%c%c%c",
                candidates[i][1][0], candidates[i][1][1], candidates[i][1][2], candidates[i][1][3], // YYYY
                candidates[i][1][5], candidates[i][1][6], // MM
                candidates[i][1][8], candidates[i][1][9]); // DD
            formatted_birthdate[8] = '\0'; // null terminator �߰�

            printf("%s(%d) | %s | %s  | %s | %s | %s | %s | %s | ����� | %s\n",
                candidates[i][0], age, formatted_birthdate, convert_gender(candidates[i][2]), candidates[i][3],
                candidates[i][4], candidates[i][5], candidates[i][6], candidates[i][7], candidates[i][9]);
        
            // �ڱ�Ұ� ���
            printf("        -------------------------------------------------------------------------------------\n");
            printf("%s\n", candidates[i][10]); // �ڱ�Ұ� ���
            printf("---------------------------------------------------------------------------------------------\n");
        }
    }

    printf("==============================================================================================\n");
}

int main() {
    // �׷�� �Է� �ޱ�
    char group_name[50];
    char ch;
    int i = 0;

    printf("����� �׷���� �Է��ϼ���: ");
    while ((ch = getchar()) != '\n' && i < sizeof(group_name) - 1) { // '\n'�� �Էµ� ������ ����
        group_name[i++] = ch; // ���ڸ� ����
    }
    group_name[i] = '\0'; // null terminator �߰�

    // �ĺ��� �����͸� ������ �迭���� ������ �迭
    char* candidates[6][11] = {
        {candidate01[0], candidate01[1], candidate01[2], candidate01[3], candidate01[4], candidate01[5], candidate01[6], candidate01[7], candidate01[8], candidate01[9], candidate01[10]},
        {candidate02[0], candidate02[1], candidate02[2], candidate02[3], candidate02[4], candidate02[5], candidate02[6], candidate02[7], candidate02[8], candidate02[9], candidate02[10]},
        {candidate03[0], candidate03[1], candidate03[2], candidate03[3], candidate03[4], candidate03[5], candidate03[6], candidate03[7], candidate03[8], candidate03[9], candidate03[10]},
        {candidate04[0], candidate04[1], candidate04[2], candidate04[3], candidate04[4], candidate04[5], candidate04[6], candidate04[7], candidate04[8], candidate04[9], candidate04[10]},
        {candidate05[0], candidate05[1], candidate05[2], candidate05[3], candidate05[4], candidate05[5], candidate05[6], candidate05[7], candidate05[8], candidate05[9], candidate05[10]},
        {candidate06[0], candidate06[1], candidate06[2], candidate06[3], candidate06[4], candidate06[5], candidate06[6], candidate06[7], candidate06[8], candidate06[9], candidate06[10]}
    };

    // �ĺ��� ���� �Է�
    for (int i = 0; i < 6; i++) {
        if (i == 0) {
            // ù ��° �ĺ����� �� ���
            printf("\n####################################\n");
            printf("[%s] ����� �ĺ��� ������ �Է�\n", group_name);
            printf("####################################\n");
            printf("ù ��° �ĺ����� ������ �Է��մϴ�.\n");
            printf("---------------------------------\n");
        }
        else {
            // �� ��° ���� �ĺ����� �� ���
            printf("\n=================================\n");
            printf("%s �ĺ��ڸ� �Է��մϴ�.\n", (i == 1) ? "�� ��°" : (i == 2) ? "�� ��°" : (i == 3) ? "�� ��°" : (i == 4) ? "�ټ� ��°" : "���� ��°");
            printf("---------------------------------\n");
        }

        // �ĺ����� ���� �Է�
        for (int j = 0; j < 11; j++) {
            printf("%d. %s: ", j + 1, member_info[j]);  // �� �Է� �տ� ��ȣ �߰�
            fgets(candidates[i][j], 100, stdin);
            remove_newline(candidates[i][j]);  // ���� ���� ����
        }
    }

    // ��� �ĺ��� ������ �Է��� �Ŀ� ��ü �ĺ��� ������ ���
    print_all_candidates_data(candidates, group_name);

    return 0;
}
