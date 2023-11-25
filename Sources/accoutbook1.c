#include <stdio.h>
#include <string.h>

#define MAX_CATEGORIES 4
#define MAX_EXPENSES 100
#define MAX_DETAIL_LENGTH 50

int main() {
    char categories[MAX_CATEGORIES][20] = { "�ĺ�", "�б���Ȱ", "�Ƿ�", "��Ÿ" };
    int expenses_count[MAX_CATEGORIES] = { 0 };
    char expenses[MAX_CATEGORIES][MAX_EXPENSES][MAX_DETAIL_LENGTH];

    printf("ī�װ��� �����ϼ���:\n");
    for (int i = 0; i < MAX_CATEGORIES; i++) {
        printf("%d. %s\n", i + 1, categories[i]);
    }

    int category_choice;
    printf("����(1-%d): ", MAX_CATEGORIES);
    scanf_s("%d", &category_choice);

    if (category_choice < 1 || category_choice > MAX_CATEGORIES) {
        printf("�߸��� �����Դϴ�.\n");
        return 1;
    }

    printf("%s�� �����ϼ̽��ϴ�.\n", categories[category_choice - 1]);

    char detail[MAX_DETAIL_LENGTH];
    printf("���� ������ ������ ������ �Է����ּ��� (��: ���ĸ�:���� ���� ����:): ");
    scanf_s(" %[^\n]", detail);

    int len = strlen(detail);
    if (len < MAX_DETAIL_LENGTH) {
        int i;
        for (i = 0; i < len && i < MAX_DETAIL_LENGTH - 1; i++) {
            expenses[category_choice - 1][expenses_count[category_choice - 1]][i] = detail[i];
        }
        expenses[category_choice - 1][expenses_count[category_choice - 1]][i] = '\0';
        expenses_count[category_choice - 1]++;
        printf("������ ���������� �߰��Ǿ����ϴ�!\n");
    }
    else {
        printf("�Է��� �ʹ� ��ϴ�.\n");
    }

    printf("\n%s�� ���� ����:\n", categories[category_choice - 1]);
    for (int i = 0; i < expenses_count[category_choice - 1]; i++) {
        printf("%d. %s\n", i + 1, expenses[category_choice - 1][i]);
    }

    return 0;
}
