#include <stdio.h>
#include <string.h>

#define MAX_CATEGORIES 4
#define MAX_EXPENSES 100
#define MAX_DETAIL_LENGTH 50

void saveExpenseToFile(const char* category, const char* detail, int* cardCount, int* cashCount, int* otherCount) {
    FILE* file;
    if (fopen_s(&file, category, "a") != 0) {
        printf("������ �� �� �����ϴ�.\n");
        return;
    }

    fprintf(file, "%s\n", detail); // Write detail to the file
    fclose(file);

    if (strstr(detail, "ī��") != NULL) {
        (*cardCount)++;
    }
    else if (strstr(detail, "����") != NULL) {
        (*cashCount)++;
    }
    else if (strstr(detail, "��Ÿ") != NULL) {
        (*otherCount)++;
    }
}

void showExpenseFromFile(const char* category, int cardCount, int cashCount, int otherCount) {
    FILE* file;
    if (fopen_s(&file, category, "r") != 0) {
        printf("������ �� �� �����ϴ�.\n");
        return;
    }

    printf("\n%s�� ���� ����:\n", category);
    char line[MAX_DETAIL_LENGTH];
    int count = 0;
    while (fgets(line, sizeof(line), file) != NULL) {
        line[strcspn(line, "\n")] = 0; // Remove newline character if present
        printf("%d. %s\n", ++count, line); // Display expense detail
    }

    printf("\nī��: %dȸ, ����: %dȸ, ��Ÿ: %dȸ\n", cardCount, cashCount, otherCount);

    fclose(file);
}

int main() {
    char categories[MAX_CATEGORIES][20] = { "�ĺ�", "�б���Ȱ", "�Ƿ�", "��Ÿ" };
    int expenses_count[MAX_CATEGORIES] = { 0 };
    int cardCount = 0, cashCount = 0, otherCount = 0;

    printf("ī�װ��� �����ϼ���:\n");
    for (int i = 0; i < MAX_CATEGORIES; i++) {
        printf("%d. %s\n", i + 1, categories[i]);
    }

    while (1) {
        int category_choice;
        printf("����(1-%d) (0�� �Է��ϸ� ����): ", MAX_CATEGORIES);
        scanf_s("%d", &category_choice);

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
        printf("���� ���� �� ������ ������ �Է����ּ��� (��: ���ĸ�:���� ���� ���): ");
        getchar(); // Clear input buffer
        fgets(detail, sizeof(detail), stdin);
        detail[strcspn(detail, "\n")] = 0; // Remove newline character if present

        if (strlen(detail) >= MAX_DETAIL_LENGTH) {
            printf("�Է��� �ʹ� ��ϴ�.\n");
            continue;
        }

        printf("���� ����� �����ϼ��� (1. ī��, 2. ����, 3. ��Ÿ): ");
        int method_choice;
        scanf_s("%d", &method_choice);

        switch (method_choice) {
        case 1:
            strcat_s(detail, MAX_DETAIL_LENGTH, " (ī��)");
            break;
        case 2:
            strcat_s(detail, MAX_DETAIL_LENGTH, " (����)");
            break;
        case 3:
            strcat_s(detail, MAX_DETAIL_LENGTH, " (��Ÿ)");
            break;
        default:
            printf("�߸��� �����Դϴ�.\n");
            continue;
        }

        saveExpenseToFile(categories[category_choice - 1], detail, &cardCount, &cashCount, &otherCount);
        expenses_count[category_choice - 1]++;
        printf("������ ���������� �߰��Ǿ����ϴ�!\n");

        showExpenseFromFile(categories[category_choice - 1], cardCount, cashCount, otherCount);
    }

    return 0;
}
