#include <stdio.h>
#include <string.h>

#define MAX_CATEGORIES 4
#define MAX_EXPENSES 100
#define MAX_DETAIL_LENGTH 50

void saveExpenseToFile(const char* category, const char* detail) {
    FILE* file;
    if (fopen_s(&file, category, "a") != 0) {
        printf("������ �� �� �����ϴ�.\n");
        return;
    }

    fprintf(file, "%s\n", detail); // Write detail to the file
    fclose(file);
}

void showExpenseFromFile(const char* category) {
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

    fclose(file);
}

int main() {
    char categories[MAX_CATEGORIES][20] = { "�ĺ�", "�б���Ȱ", "�Ƿ�", "��Ÿ" };
    int expenses_count[MAX_CATEGORIES] = { 0 };

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
        printf("���� ���� �� ������ ������ �Է����ּ��� (��: ���ĸ�:���� ���� ����:): ");
        getchar(); // Clear input buffer
        fgets(detail, sizeof(detail), stdin);
        detail[strcspn(detail, "\n")] = 0; // Remove newline character if present

        if (strlen(detail) >= MAX_DETAIL_LENGTH) {
            printf("�Է��� �ʹ� ��ϴ�.\n");
            continue;
        }

        saveExpenseToFile(categories[category_choice - 1], detail);
        expenses_count[category_choice - 1]++;
        printf("������ ���������� �߰��Ǿ����ϴ�!\n");

        showExpenseFromFile(categories[category_choice - 1]);
    }

    return 0;
}
