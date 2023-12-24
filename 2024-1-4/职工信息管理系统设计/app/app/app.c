#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORKERS 100
#define MAX_NAME_LENGTH 50

struct Worker {
	int id;
	char name[MAX_NAME_LENGTH];
	char gender[20];
	char birthdate[11];
	char education[20];
	float salary;
	char address[100];
	char phone[20];
};

struct Worker workers[MAX_WORKERS];
int numWorkers = 0;

void displayMenu() {
	printf("\n\n==== 职工信息管理系统 ====\n");
	printf("1. 录入职工信息\n");
	printf("2. 浏览职工信息\n");
	printf("3. 查询职工信息\n");
	printf("0. 退出系统\n");
	printf("=========================\n");
	printf("请输入您的选择：");
}

void addWorker() {
	if (numWorkers >= MAX_WORKERS) {
		printf("职工数量已满，无法继续录入。\n");
		return;
	}

	struct Worker newWorker;
	printf("请输入职工号：");
	scanf("%d", &newWorker.id);
	getchar(); // 消费掉输入缓冲区中的换行符

	// 检查职工号是否重复
	for (int i = 0; i < numWorkers; i++) {
		if (workers[i].id == newWorker.id) {
			printf("职工号已存在，请重新输入。\n");
			return;
		}
	}

	printf("请输入姓名：");
	scanf("%s",newWorker.name);
	

	printf("请输入性别：");
	scanf("%s", newWorker.gender);
	

	printf("请输入出生日期（格式：yyyy-mm-dd）：");
	scanf("%s", newWorker.birthdate);

	printf("请输入学历：");
	scanf("%s", newWorker.education);

	printf("请输入工资：");
	scanf("%f", &newWorker.salary);
	getchar();

	printf("请输入住址：");
	scanf("%s", newWorker.address);
	getchar();

	printf("请输入电话：");
	scanf("%s", newWorker.phone);
	
	workers[numWorkers] = newWorker;
	numWorkers++;

	printf("职工信息录入成功。\n");
}

void displayWorkers() {
	if (numWorkers == 0) {
		printf("暂无职工信息。\n");
		return;
	}

	printf("==== 职工信息浏览 ====\n");
	for (int i = 0; i < numWorkers; i++) {
		struct Worker worker = workers[i];
		printf("职工号: %d\n", worker.id);
		printf("姓名: %s\n", worker.name);
		printf("性别: %s\n", worker.gender);
		printf("出生日期: %s\n", worker.birthdate);
		printf("学历: %s\n", worker.education);
		printf("工资: %.2f\n", worker.salary);
		printf("住址: %s\n", worker.address);
		printf("电话: %s\n", worker.phone);
		printf("======================\n");
	}
}

void searchWorker() {
	if (numWorkers == 0) {
		printf("暂无职工信息。\n");
		return;
	}

	int choice;
	printf("请选择查询方式：\n");
	printf("1. 按学历查询\n");
	printf("2. 按职工号查询\n");
	printf("请输入您的选择：");
	scanf("%d", &choice);
	getchar();

	switch (choice) {
	case 1:
		printf("请输入学历：");
		char education[20];
		scanf("%s", education);
			
		printf("==== 学历为 %s 的职工信息 ====\n", education);
		for (int i = 0; i < numWorkers; i++) {
			struct Worker worker = workers[i];
			if (strcmp(worker.education, education) == 0) {
				printf("职工号: %d\n", worker.id);
				printf("姓名: %s\n", worker.name);
				printf("性别: %s\n", worker.gender);
				printf("出生日期: %s\n", worker.birthdate);
				printf("学历: %s\n", worker.education);
				printf("工资: %.2f\n", worker.salary);
				printf("住址: %s\n", worker.address);
				printf("电话: %s\n", worker.phone);
				printf("======================\n");
			}
		}
		break;
	case 2:
		printf("请输入职工号：");
		int id;
		scanf("%d", &id);
		getchar();

		printf("==== 职工号为 %d 的职工信息 ====\n", id);
		for (int i = 0; i < numWorkers; i++) {
			struct Worker worker = workers[i];
			if (worker.id == id) {
				printf("职工号: %d\n", worker.id);
				printf("姓名: %s\n", worker.name);
				printf("性别: %s\n", worker.gender);
				printf("出生日期: %s\n", worker.birthdate);
				printf("学历: %s\n", worker.education);
				printf("工资: %.2f\n", worker.salary);
				printf("住址: %s\n", worker.address);
				printf("电话: %s\n", worker.phone);
				printf("======================\n");
				break;
			}
		}
		break;
	default:
		printf("无效的选择。\n");
		return;
	}
}

void saveWorkersToFile() {
	FILE* file = fopen("workers.txt", "w");
	if (file == NULL) {
		printf("无法保存职工信息到文件。\n");
		return;
	}

	for (int i = 0; i < numWorkers; i++) {
		struct Worker worker = workers[i];
		fprintf(file, "%d,%s,%s,%s,%s,%.2f,%s,%s\n", worker.id, worker.name,
			worker.gender, worker.birthdate, worker.education, worker.salary,
			worker.address, worker.phone);
	}

	fclose(file);
	printf("职工信息保存成功。\n");
}

void loadWorkersFromFile() {
	FILE* file = fopen("workers.txt", "r");
	if (file == NULL) {
		printf("无法从文件加载职工信息。\n");
		return;
	}

	numWorkers = 0;
	while (!feof(file) && numWorkers < MAX_WORKERS) {
		struct Worker worker;
		fscanf(file, "%d,%[^,],%[^,],%[^,],%[^,],%f,%[^,],%[^\n]\n", &worker.id, worker.name,
			worker.gender, worker.birthdate, worker.education, &worker.salary,
			worker.address, worker.phone);
		workers[numWorkers] = worker;
		numWorkers++;
	}

	fclose(file);
	printf("职工信息加载成功。\n");
}

int main() {
	int choice;

	loadWorkersFromFile();

	do {
		displayMenu();
		scanf("%d", &choice);
		getchar(); // 消费掉输入缓冲区中的换行符

		switch (choice) {
		case 1:
			addWorker();
			break;
		case 2:
			displayWorkers();
			break;
		case 3:
			searchWorker();
			break;
		case 0:
			saveWorkersToFile();
			printf("感谢使用职工信息管理系统，再见！\n");
			break;
		default:
			printf("无效的选择，请重新输入。\n");
			break;
		}
	} while (choice != 0);

	return 0;
}