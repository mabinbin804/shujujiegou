#include <stdio.h>
#include <stdlib.h>
#include <string>


//�˵�
void menu()
{
    printf("*************���˵�**************");
    printf("(1����֪һ�����Ų�ѯ�ò��ŵ�ֱ���ϼ�����\n");
    printf("(2)��֪һ�����Ų�ѯ����ֱ����������\n");
    printf("(3)��ѯһ�����ŵļ���\n");
    printf("(4)��ѯһ�����ŵ��ֵܲ�����Ϣ\n");
    printf("(5����ѯĳ���ŵ����и�������ϼ�����\n");
}
// �������������ṹ��
typedef struct administrative_department {
    char name[50]; // ��������
    char introduction[100]; // ҵ����
    char phone[20]; // �칫�绰
    char address[100]; // �칫��ַ
    struct administrative_department* parent; // ������
    struct administrative_department* child; // �Ӳ���
    int childnum;//���Ӳ�������
} Department; 

// �����������ڵ�
Department* createDepartment(char name[], char introduction[], char phone[], char address[]) {
    Department* department = (Department*)malloc(sizeof(Department));
    strcpy(department->name, name);
    strcpy(department->introduction, introduction);
    strcpy(department->phone, phone);
    strcpy(department->address, address);
    department->parent = NULL;
    department->child = NULL;
    department->childnum = 0;
    return department;
}

// �ڸ�����������Ӳ���
void addChildDepartment(Department* parent, Department* child) {
    if (parent->child == NULL) {
        parent->child = child;
    }
    else {
        Department* t = parent->child;
        while (t->sibling != NULL) {
            t = t->sibling;                                                                                              
        }
        t->sibling = child;
    }
    child->parent = parent;
}

// ��ѯһ�����ŵ�ֱ���ϼ�����
Department* getParentDepartment(Department* department) {
    return department->parent;
}

// ��ѯһ�����ŵ�ֱ����������
Department* getChildDepartment(Department* department) {
    return department->child;
}

// ��ѯһ�����ŵļ���
int getDepartmentLevel(Department* department) {
    int level = 0;
    Department* parent = department->parent;
    while (parent != NULL) {
        level++;
        parent = parent->parent;
    }
    return level;
}

// ��ѯһ�����ŵ��ֵܲ�����Ϣ
void printSiblingDepartmentInfo(Department* department) {
    Department* sibling = department->parent->child;
    while (sibling != NULL) {
        if (strcmp(sibling->name, department->name) != 0) {
            printf("%s\n", sibling->name);
            printf("  ҵ����: %s\n", sibling->introduction);
            printf("  �칫�绰: %s\n", sibling->phone);
            printf("  �칫��ַ: %s\n", sibling->address);
            printf("\n");
        }
        sibling = sibling->sibling;
    }
}

// ��ѯĳ���ŵ����и�������ϼ�������Ϣ
void printAllParentDepartmentInfo(Department* department) {
    Department* parent = department->parent;
    while (parent != NULL) {
        printf("%s\n", parent->name);
        printf("  ҵ����: %s\n", parent->introduction);
        printf("  �칫�绰: %s\n", parent->phone);
        printf("  �칫��ַ: %s\n", parent->address);
        printf("\n");
        parent = parent->parent;
    }
}

// ������Ϣ
void printDepartmentInfo(Department* department, int level) {
    for (int i = 0; i < level; i++) {
        printf("-");
    }
    printf("%s\n", department->name);
    printf("  ҵ����: %s\n", department->introduction);
    printf("  �칫�绰: %s\n", department->phone);
    printf("  �칫��ַ: %s\n", department->address);
    printf("\n");
    Department* child = department->child;
    while (child != NULL) {
        printDepartmentInfo(child, level + 1);
        child = child->sibling;
    }
}

int main() {
    // ����������������
    Department* root = createDepartment("��λ�ܲ�", "", "", "");

    Department* department1 = createDepartment("����1", "����1ҵ����", "����1�칫�绰", "����1�칫��ַ");
    addChildDepartment(root, department1);

    Department* department2 = createDepartment("����2", "����2ҵ���", "����2�칫�绰", "����2�칫��ַ");
    addChildDepartment(root, department2);

    Department* department3 = createDepartment("����3", "����3ҵ����", "����3�칫�绰", "����3�칫��ַ");
    addChildDepartment(department1, department3);

    Department* department4 = createDepartment("����4", "����4ҵ����", "����4�칫�绰", "����4�칫��ַ");
    addChildDepartment(department1, department4);

    // ��ѯ����ӡ����������Ϣ
    printDepartmentInfo(root, 0);

    // ��ѯ����1�ĸ����ź��ֵܲ�����Ϣ
    Department* parent1 = getParentDepartment(department1);
    printf("����1�ĸ�������Ϣ��\n");
    printf("%s\n", parent1->name);
    printf("  ҵ����: %s\n", parent1->introduction);
    printf("  �칫�绰: %s\n", parent1->phone);
    printf("  �칫��ַ: %s\n", parent1->address);
    printf("\n");

    printf("����1���ֵܲ�����Ϣ��\n");
    printSiblingDepartmentInfo(department1);

    // ��ѯ����3�ļ���������ϼ�������Ϣ
    int level3 = getDepartmentLevel(department3);
    printf("����3�ļ���Ϊ��%d\n", level3);
    printf("����3���ϼ�������Ϣ��\n");
    printAllParentDepartmentInfo(department3);

    return 0;
}
