#include <stdio.h>
#include <string.h>

#define MAX_CATEGORIES 4
#define MAX_EXPENSES 100
#define MAX_DETAIL_LENGTH 50

int main() {
    char categories[MAX_CATEGORIES][20] = { "식비", "학교생활", "의류", "기타" };
    int expenses_count[MAX_CATEGORIES] = { 0 };
    char expenses[MAX_CATEGORIES][MAX_EXPENSES][MAX_DETAIL_LENGTH];

    printf("카테고리를 선택하세요:\n");
    for (int i = 0; i < MAX_CATEGORIES; i++) {
        printf("%d. %s\n", i + 1, categories[i]);
    }

    int category_choice;
    printf("선택(1-%d): ", MAX_CATEGORIES);
    scanf_s("%d", &category_choice);

    if (category_choice < 1 || category_choice > MAX_CATEGORIES) {
        printf("잘못된 선택입니다.\n");
        return 1;
    }

    printf("%s를 선택하셨습니다.\n", categories[category_choice - 1]);

    char detail[MAX_DETAIL_LENGTH];
    printf("세부 내역및 지출의 이유를 입력해주세요 (예: 음식명:가격 지출 이유:): ");
    scanf_s(" %[^\n]", detail);

    int len = strlen(detail);
    if (len < MAX_DETAIL_LENGTH) {
        int i;
        for (i = 0; i < len && i < MAX_DETAIL_LENGTH - 1; i++) {
            expenses[category_choice - 1][expenses_count[category_choice - 1]][i] = detail[i];
        }
        expenses[category_choice - 1][expenses_count[category_choice - 1]][i] = '\0';
        expenses_count[category_choice - 1]++;
        printf("지출이 성공적으로 추가되었습니다!\n");
    }
    else {
        printf("입력이 너무 깁니다.\n");
    }

    printf("\n%s의 지출 내역:\n", categories[category_choice - 1]);
    for (int i = 0; i < expenses_count[category_choice - 1]; i++) {
        printf("%d. %s\n", i + 1, expenses[category_choice - 1][i]);
    }

    return 0;
}
