#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

#define MAX_CATEGORIES 4
#define MAX_DETAIL_LENGTH 50
#define MAX_EXPENSES 100


struct Expense {
    char category[20];
    char detail[MAX_DETAIL_LENGTH];
    int cardCount;
    int cashCount;
    int otherCount;
};


void saveExpenseToFile(struct Expense* expense);
void showExpenseFromFile(struct Expense* expense);


void saveExpenseToFile(struct Expense* expense) {
    FILE* file;
    if (fopen_s(&file, expense->category, "a") != 0) {
        printf("파일을 열 수 없습니다.\n");
        return;
    }

    fprintf(file, "%s\n", expense->detail);
    fclose(file);

    if (strstr(expense->detail, "(카드)") != NULL) {
        expense->cardCount++;
    }
    else if (strstr(expense->detail, "(현금)") != NULL) {
        expense->cashCount++;
    }
    else if (strstr(expense->detail, "(기타)") != NULL) {
        expense->otherCount++;
    }
}


void showExpenseFromFile(struct Expense* expense) {
    FILE* file;
    if (fopen_s(&file, expense->category, "r") != 0) {
        printf("파일을 열 수 없습니다.\n");
        return;
    }

    printf("\n%s의 지출 내역:\n", expense->category);
    char line[MAX_DETAIL_LENGTH];
    int count = 0;
    while (fgets(line, sizeof(line), file) != NULL) {
        line[strcspn(line, "\n")] = 0;
        printf("%d. %s\n", ++count, line);
    }

    printf("\n카드: %d회, 현금: %d회, 기타: %d회\n", expense->cardCount, expense->cashCount, expense->otherCount);

    fclose(file);
}

int main() {
    char categories[MAX_CATEGORIES][20] = { "식비", "학교생활", "의류", "기타" };
    struct Expense expenses[MAX_CATEGORIES];
    int cardCount = 0, cashCount = 0, otherCount = 0;

    for (int i = 0; i < MAX_CATEGORIES; ++i) {
        strcpy(expenses[i].category, categories[i]);
        expenses[i].cardCount = 0;
        expenses[i].cashCount = 0;
        expenses[i].otherCount = 0;
    }

    printf("카테고리를 선택하세요:\n");
    for (int i = 0; i < MAX_CATEGORIES; i++) {
        printf("%d. %s\n", i + 1, categories[i]);
    }

    while (1) {
        int category_choice;
        printf("선택(1-%d) (0을 입력하면 종료): ", MAX_CATEGORIES);
        scanf("%d", &category_choice);

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
        printf("세부 내역 및 지출의 이유를 입력해주세요 (예: 음식명:가격): ");
        getchar();
        fgets(detail, sizeof(detail), stdin);
        detail[strcspn(detail, "\n")] = 0;

        if (strlen(detail) >= MAX_DETAIL_LENGTH) {
            printf("입력이 너무 깁니다.\n");
            continue;
        }

        printf("지출 방법을 선택하세요 (1. 카드, 2. 현금, 3. 기타): ");
        int method_choice;
        scanf("%d", &method_choice);

        switch (method_choice) {
        case 1:
            strcat_s(detail, sizeof(detail), " (카드)");
            cardCount++;
            break;
        case 2:
            strcat_s(detail, sizeof(detail), " (현금)");
            cashCount++;
            break;
        case 3:
            strcat_s(detail, sizeof(detail), " (기타)");
            otherCount++;
            break;
        default:
            printf("잘못된 선택입니다.\n");
            continue;
        }

        struct Expense currentExpense;
        strcpy(currentExpense.category, categories[category_choice - 1]);
        strcpy(currentExpense.detail, detail);

        saveExpenseToFile(&currentExpense);
        int index = category_choice - 1;
        expenses[index].cardCount = cardCount;
        expenses[index].cashCount = cashCount;
        expenses[index].otherCount = otherCount;

        printf("지출이 성공적으로 추가되었습니다!\n");
        showExpenseFromFile(&expenses[index]);
    }

    return 0;
}
