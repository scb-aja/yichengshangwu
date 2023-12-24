#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMPLOYEES 100
#define INFO_LENGTH 50
#define FILENAME "employees.txt"

typedef struct {
	char id[INFO_LENGTH];
	char name[INFO_LENGTH];
	char gender[INFO_LENGTH];
	char birthDate[INFO_LENGTH];
	char education[INFO_LENGTH];
	double salary;
	char address[INFO_LENGTH];
	char phone[INFO_LENGTH];
} Employee;

Employee employees[MAX_EMPLOYEES];
int employeeCount = 0;

void addEmployee() {
	if (employeeCount >= MAX_EMPLOYEES) {
		printf("无法录入.\n");
		return;
	}

	Employee e;
	printf("ID: ");
	scanf("%s", e.id);
	printf("请输入姓名: ");
	scanf("%s", e.name);
	printf("请输入性别: ");
	scanf("%s", e.gender);
	printf("请输入出生日期: ");
	scanf("%s", e.birthDate);
	printf("请输入学历: ");
	scanf("%s", e.education);
	printf("请输入薪水: ");
	scanf("%lf", &e.salary);
	printf("请输入地址: ");
	scanf("%s", e.address);
	printf("请输入电话号: ");
	scanf("%s", e.phone);

	employees[employeeCount++] = e;
	printf("添加成功.\n");
}
void saveEmployeesToFile() {
	FILE* file = fopen(FILENAME, "w");
	if (file == NULL) {
		printf("无法打开文件.\n");
		return;
	}

	for (int i = 0; i < employeeCount; i++) {
		fprintf(file, "%s %s %s %s %s %lf %s %s\n",
			employees[i].id, employees[i].name, employees[i].gender,
			employees[i].birthDate, employees[i].education,
			employees[i].salary, employees[i].address, employees[i].phone);
	}

	fclose(file);
	printf("员工成功保存到文件.\n");
}
void displayEmployees() {
	for (int i = 0; i < employeeCount; i++) {
		printf("ID: %s, 姓名: %s, 性别: %s, 出生日期: %s, 学历: %s, 薪水: %.2lf, 住址: %s, 手机号: %s\n",
			employees[i].id, employees[i].name, employees[i].gender,
			employees[i].birthDate, employees[i].education,
			employees[i].salary, employees[i].address, employees[i].phone);
	}
}


void searchEmployees() {
	char searchCriteria[INFO_LENGTH];
	printf("请输入员工 (ID/学历): ");
	scanf("%s", searchCriteria);

	for (int i = 0; i < employeeCount; i++) {
		if (strcmp(employees[i].id, searchCriteria) == 0 ||
			strcmp(employees[i].education, searchCriteria) == 0) {
			printf("ID: %s, 姓名: %s, 性别: %s, 出生日期: %s, 学历: %s, 薪水: %.2lf, 住址: %s, 手机号: %s\n",
				employees[i].id, employees[i].name, employees[i].gender,
				employees[i].birthDate, employees[i].education,
				employees[i].salary, employees[i].address, employees[i].phone);
		}
	}
}
void menu() {
	int choice;
	do {
		printf("\n1. 添加员工\n");
		printf("2. 显示所有员工\n");
		printf("3. 查找员工\n");
		printf("4. 保存到文件\n");
		printf("0. 退出\n");
		printf("请输入选项: ");
		scanf("%d", &choice);

		switch (choice) {
		case 1:
			addEmployee();
			break;
		case 2:
			displayEmployees();
			break;
		case 3:
			searchEmployees();
			break;
		case 4:
			saveEmployeesToFile();
			break;
		case 0:
			printf("退出系统\n");
			break;
		default:
			printf("错误的选项.\n");
		}
	} while (choice != 0);
}

int main() {
	menu();
	return 0;
}