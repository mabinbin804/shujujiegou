#include <stdio.h>
#include <stdlib.h>
#include <string>


//菜单
void menu()
{
    printf("*************主菜单**************");
    printf("(1）已知一个部门查询该部门的直接上级部门\n");
    printf("(2)已知一个部门查询他的直接下属部门\n");
    printf("(3)查询一个部门的级别\n");
    printf("(4)查询一个部门的兄弟部门信息\n");
    printf("(5）查询某部门的所有各级别的上级部门\n");
}
// 定义行政机构结构体
typedef struct administrative_department {
    char name[50]; // 部门名称
    char introduction[100]; // 业务简介
    char phone[20]; // 办公电话
    char address[100]; // 办公地址
    struct administrative_department* parent; // 父部门
    struct administrative_department* child; // 子部门
    int childnum;//孩子部门数量
} Department; 

// 创建行政机节点
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

// 在父部门中添加子部门
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

// 查询一个部门的直接上级部门
Department* getParentDepartment(Department* department) {
    return department->parent;
}

// 查询一个部门的直接下属部门
Department* getChildDepartment(Department* department) {
    return department->child;
}

// 查询一个部门的级别
int getDepartmentLevel(Department* department) {
    int level = 0;
    Department* parent = department->parent;
    while (parent != NULL) {
        level++;
        parent = parent->parent;
    }
    return level;
}

// 查询一个部门的兄弟部门信息
void printSiblingDepartmentInfo(Department* department) {
    Department* sibling = department->parent->child;
    while (sibling != NULL) {
        if (strcmp(sibling->name, department->name) != 0) {
            printf("%s\n", sibling->name);
            printf("  业务简介: %s\n", sibling->introduction);
            printf("  办公电话: %s\n", sibling->phone);
            printf("  办公地址: %s\n", sibling->address);
            printf("\n");
        }
        sibling = sibling->sibling;
    }
}

// 查询某部门的所有各级别的上级部门信息
void printAllParentDepartmentInfo(Department* department) {
    Department* parent = department->parent;
    while (parent != NULL) {
        printf("%s\n", parent->name);
        printf("  业务简介: %s\n", parent->introduction);
        printf("  办公电话: %s\n", parent->phone);
        printf("  办公地址: %s\n", parent->address);
        printf("\n");
        parent = parent->parent;
    }
}

// 打部门信息
void printDepartmentInfo(Department* department, int level) {
    for (int i = 0; i < level; i++) {
        printf("-");
    }
    printf("%s\n", department->name);
    printf("  业务简介: %s\n", department->introduction);
    printf("  办公电话: %s\n", department->phone);
    printf("  办公地址: %s\n", department->address);
    printf("\n");
    Department* child = department->child;
    while (child != NULL) {
        printDepartmentInfo(child, level + 1);
        child = child->sibling;
    }
}

int main() {
    // 创建各级行政机构
    Department* root = createDepartment("单位总部", "", "", "");

    Department* department1 = createDepartment("部门1", "部门1业务简介", "部门1办公电话", "部门1办公地址");
    addChildDepartment(root, department1);

    Department* department2 = createDepartment("部门2", "部门2业简介", "部门2办公电话", "部门2办公地址");
    addChildDepartment(root, department2);

    Department* department3 = createDepartment("部门3", "部门3业务简介", "部门3办公电话", "部门3办公地址");
    addChildDepartment(department1, department3);

    Department* department4 = createDepartment("部门4", "部门4业务简介", "部门4办公电话", "部门4办公地址");
    addChildDepartment(department1, department4);

    // 查询并打印行政机构信息
    printDepartmentInfo(root, 0);

    // 查询部门1的父部门和兄弟部门信息
    Department* parent1 = getParentDepartment(department1);
    printf("部门1的父部门信息：\n");
    printf("%s\n", parent1->name);
    printf("  业务简介: %s\n", parent1->introduction);
    printf("  办公电话: %s\n", parent1->phone);
    printf("  办公地址: %s\n", parent1->address);
    printf("\n");

    printf("部门1的兄弟部门信息：\n");
    printSiblingDepartmentInfo(department1);

    // 查询部门3的级别和所有上级部门信息
    int level3 = getDepartmentLevel(department3);
    printf("部门3的级别为：%d\n", level3);
    printf("部门3的上级部门信息：\n");
    printAllParentDepartmentInfo(department3);

    return 0;
}
