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
        printf("������ �� �� �����ϴ�.\n");
        return;
    }

    fprintf(file, "%s\n", expense->detail);
    fclose(file);

    if (strstr(expense->detail, "(ī��)") != NULL) {
        expense->cardCount++;
    }
    else if (strstr(expense->detail, "(����)") != NULL) {
        expense->cashCount++;
    }
    else if (strstr(expense->detail, "(��Ÿ)") != NULL) {
        expense->otherCount++;
    }
}


void showExpenseFromFile(struct Expense* expense) {
    FILE* file;
    if (fopen_s(&file, expense->category, "r") != 0) {
        printf("������ �� �� �����ϴ�.\n");
        return;
    }

    printf("\n%s�� ���� ����:\n", expense->category);
    char line[MAX_DETAIL_LENGTH];
    int count = 0;
    while (fgets(line, sizeof(line), file) != NULL) {
        line[strcspn(line, "\n")] = 0;
        printf("%d. %s\n", ++count, line);
    }

    printf("\nī��: %dȸ, ����: %dȸ, ��Ÿ: %dȸ\n", expense->cardCount, expense->cashCount, expense->otherCount);

    fclose(file);
}

int main() {
    char categories[MAX_CATEGORIES][20] = { "�ĺ�", "�б���Ȱ", "�Ƿ�", "��Ÿ" };
    struct Expense expenses[MAX_CATEGORIES];
    int cardCount = 0, cashCount = 0, otherCount = 0;

    for (int i = 0; i < MAX_CATEGORIES; ++i) {
        strcpy(expenses[i].category, categories[i]);
        expenses[i].cardCount = 0;
        expenses[i].cashCount = 0;
        expenses[i].otherCount = 0;
    }

    printf("ī�װ��� �����ϼ���:\n");
    for (int i = 0; i < MAX_CATEGORIES; i++) {
        printf("%d. %s\n", i + 1, categories[i]);
    }

    while (1) {
        int category_choice;
        printf("����(1-%d) (0�� �Է��ϸ� ����): ", MAX_CATEGORIES);
        scanf("%d", &category_choice);

        if (category_choice == 0) {
            printf("���α׷��� �����մϴ�.\n");
            break;
        }

        if (category_choice < 1 || category_choice > MAX_CATEGORIES) {
            printf("�߸��� �����Դϴ�.\n");
            continue;
        }

        printf("%s�� �����ϼ̽��ϴ�.\n", categories[category_choice - 1]);

        char detail[MAX_DETAIL_LENGTH];
        printf("���� ���� �� ������ ������ �Է����ּ��� (��: ���ĸ�:����): ");
        getchar();
        fgets(detail, sizeof(detail), stdin);
        detail[strcspn(detail, "\n")] = 0;

        if (strlen(detail) >= MAX_DETAIL_LENGTH) {
            printf("�Է��� �ʹ� ��ϴ�.\n");
            continue;
        }

        printf("���� ����� �����ϼ��� (1. ī��, 2. ����, 3. ��Ÿ): ");
        int method_choice;
        scanf("%d", &method_choice);

        switch (method_choice) {
        case 1:
            strcat_s(detail, sizeof(detail), " (ī��)");
            cardCount++;
            break;
        case 2:
            strcat_s(detail, sizeof(detail), " (����)");
            cashCount++;
            break;
        case 3:
            strcat_s(detail, sizeof(detail), " (��Ÿ)");
            otherCount++;
            break;
        default:
            printf("�߸��� �����Դϴ�.\n");
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

        printf("������ ���������� �߰��Ǿ����ϴ�!\n");
        showExpenseFromFile(&expenses[index]);
    }

    return 0;
}
