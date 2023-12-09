#include <stdio.h>
#include <string.h>

#define MAX_CATEGORIES 4
#define MAX_EXPENSES 100
#define MAX_DETAIL_LENGTH 50

void saveExpenseToFile(const char* category, const char* detail, int* cardCount, int* cashCount, int* otherCount) {
    FILE* file;
    if (fopen_s(&file, category, "a") != 0) {
        printf("파일을 열 수 없습니다.\n");
        return;
    }

    fprintf(file, "%s\n", detail); // Write detail to the file
    fclose(file);

    if (strstr(detail, "카드") != NULL) {
        (*cardCount)++;
    }
    else if (strstr(detail, "현금") != NULL) {
        (*cashCount)++;
    }
    else if (strstr(detail, "기타") != NULL) {
        (*otherCount)++;
    }
}

void showExpenseFromFile(const char* category, int cardCount, int cashCount, int otherCount) {
    FILE* file;
    if (fopen_s(&file, category, "r") != 0) {
        printf("파일을 열 수 없습니다.\n");
        return;
    }

    printf("\n%s의 지출 내역:\n", category);
    char line[MAX_DETAIL_LENGTH];
    int count = 0;
    while (fgets(line, sizeof(line), file) != NULL) {
        line[strcspn(line, "\n")] = 0; // Remove newline character if present
        printf("%d. %s\n", ++count, line); // Display expense detail
    }

    printf("\n카드: %d회, 현금: %d회, 기타: %d회\n", cardCount, cashCount, otherCount);

    fclose(file);
}

int main() {
    char categories[MAX_CATEGORIES][20] = { "식비", "학교생활", "의류", "기타" };
    int expenses_count[MAX_CATEGORIES] = { 0 };
    int cardCount = 0, cashCount = 0, otherCount = 0;

    printf("카테고리를 선택하세요:\n");
    for (int i = 0; i < MAX_CATEGORIES; i++) {
        printf("%d. %s\n", i + 1, categories[i]);
    }

    while (1) {
        int category_choice;
        printf("선택(1-%d) (0을 입력하면 종료): ", MAX_CATEGORIES);
        scanf_s("%d", &category_choice);

        if (category_choice == 0) {
            printf("프로그램을 종료합니다.\n");
            break;
        }

        if (category_choice < 1 || category_choice > MAX_CATEGORIES) {
            printf("잘못된 선택입니다.\n");
            continue;
        }

        printf("%s를 선택하셨습니다.\n", categories[category_choice - 1]);

        char detail[MAX_DETAIL_LENGTH];
        printf("세부 내역 및 지출의 이유를 입력해주세요 (예: 음식명:가격 지출 방법): ");
        getchar(); // Clear input buffer
        fgets(detail, sizeof(detail), stdin);
        detail[strcspn(detail, "\n")] = 0; // Remove newline character if present

        if (strlen(detail) >= MAX_DETAIL_LENGTH) {
            printf("입력이 너무 깁니다.\n");
            continue;
        }

        printf("지출 방법을 선택하세요 (1. 카드, 2. 현금, 3. 기타): ");
        int method_choice;
        scanf_s("%d", &method_choice);

        switch (method_choice) {
        case 1:
            strcat_s(detail, MAX_DETAIL_LENGTH, " (카드)");
            break;
        case 2:
            strcat_s(detail, MAX_DETAIL_LENGTH, " (현금)");
            break;
        case 3:
            strcat_s(detail, MAX_DETAIL_LENGTH, " (기타)");
            break;
        default:
            printf("잘못된 선택입니다.\n");
            continue;
        }

        saveExpenseToFile(categories[category_choice - 1], detail, &cardCount, &cashCount, &otherCount);
        expenses_count[category_choice - 1]++;
        printf("지출이 성공적으로 추가되었습니다!\n");

        showExpenseFromFile(categories[category_choice - 1], cardCount, cashCount, otherCount);
    }

    return 0;
}
