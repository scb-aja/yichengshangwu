#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#define MAX_CONTACTS 100
#define MAX_NAME_LENGTH 50
#define MAX_PHONE_LENGTH 20
#define MAX_EMAIL_LENGTH 50

struct Contact {
	char name[MAX_NAME_LENGTH];
	char hometown[MAX_NAME_LENGTH];
	char phone1[MAX_PHONE_LENGTH];
	char phone2[MAX_PHONE_LENGTH];
	char email[MAX_EMAIL_LENGTH];
};
struct Contact contacts[MAX_CONTACTS];
int numContacts = 0;
int unsavedChanges = 0;

void displayMenu() {
	printf("\n\n==== 小型通讯录程序 ====\n");
	printf("1. 添加联系人\n");
	printf("2. 浏览联系人\n");
	printf("3. 查询联系人\n");
	printf("4. 修改/删除联系人\n");
	printf("5. 拨号\n");
	printf("0. 退出程序\n");
	printf("=========================\n");
	printf("请输入您的选择：");
}
void addContact() {
	if (numContacts >= MAX_CONTACTS) {
		printf("通讯录已满，无法添加新联系人。\n");
		return;
	}

	struct Contact newContact;
	printf("请输入姓名：");
	scanf("%s", newContact.name);

	printf("请输入籍贯：");
	scanf("%s", newContact.hometown);
		
	printf("请输入电话号码1：");
	scanf("%s", newContact.phone1);

	printf("请输入电话号码2：");
	scanf("%s", newContact.phone2);


	printf("请输入电子邮箱：");
	scanf("%s", newContact.email);


	contacts[numContacts] = newContact;
	numContacts++;

	unsavedChanges = 1;
	printf("联系人添加成功。\n");
}

void displayContacts() {
	if (numContacts == 0) {
		printf("通讯录中没有联系人。\n");
		return;
	}

	printf("==== 通讯录浏览 ====\n");
	for (int i = 0; i < numContacts; i++) {
		struct Contact contact = contacts[i];
		printf("姓名: %s\n", contact.name);
		printf("籍贯: %s\n", contact.hometown);
		printf("电话号码1: %s\n", contact.phone1);
		printf("电话号码2: %s\n", contact.phone2);
		printf("电子邮箱: %s\n", contact.email);
		printf("======================\n");
	}
}

void searchContact() {
	if (numContacts == 0) {
		printf("通讯录中没有联系人。\n");
		return;
	}

	char searchName[MAX_NAME_LENGTH];
	printf("请输入要查询的联系人姓名：");
	scanf("%s", searchName);

	int found = 0;
	printf("==== 查询结果 ====\n");
	for (int i = 0; i < numContacts; i++) {
		struct Contact contact = contacts[i];
		if (strcmp(contact.name, searchName) == 0) {
			printf("姓名: %s\n", contact.name);
			printf("籍贯: %s\n", contact.hometown);
			printf("电话号码1: %s\n", contact.phone1);
			printf("电话号码2: %s\n", contact.phone2);
			printf("电子邮箱: %s\n", contact.email);
			printf("======================\n");
			found = 1;
		}
	}

	if (!found) {
		printf("未找到联系人：%s\n", searchName);
	}
}

void modifyContact() {
	if (numContacts == 0) {
		printf("通讯录中没有联系人。\n");
		return;
	}

	char searchName[MAX_NAME_LENGTH];
	printf("请输入要修改/删除的联系人姓名：");
	scanf("%s", searchName);

	int found = 0;
	for (int i = 0; i < numContacts; i++) {
		struct Contact contact = contacts[i];
		if (strcmp(contact.name, searchName) == 0) {
			printf("==== 联系人信息 ====\n");
			printf("姓名: %s\n", contact.name);
			printf("籍贯: %s\n", contact.hometown);
			printf("电话号码1: %s\n", contact.phone1);
			printf("电话号码2: %s\n", contact.phone2);
			printf("电子邮箱: %s\n", contact.email);
			printf("======================\n");

			printf("请选择要进行的操作：\n");
			printf("1. 修改联系人信息\n");
			printf("2. 删除联系人\n");
			printf("0. 取消\n");
			printf("请输入您的选择：");

			int choice;
			scanf("%d", &choice);
			getchar();
			switch (choice) {
			case 1: {
				struct Contact modifiedContact;
				printf("请输入修改后的姓名：");
				getchar(); 
				scanf("%s", modifiedContact.name);

				printf("请输入修改后的籍贯：");
				scanf("%s", modifiedContact.hometown);


				printf("请输入修改后的电话号码1：");
				scanf("%s", modifiedContact.phone1);


				printf("请输入修改后的电话号码2：");
				scanf("%s", modifiedContact.phone2);

				printf("请输入修改后的电子邮箱：");
				scanf("%s", modifiedContact.email);


				contacts[i] = modifiedContact;
				unsavedChanges = 1;
				printf("联系人信息已修改。\n");
				break;
			}
			case 2:
				for (int j = i; j < numContacts - 1; j++) {
					contacts[j] = contacts[j + 1];
				}
				numContacts--;
				unsavedChanges = 1;
				printf("联系人已删除。\n");
				break;
			case 0:
				printf("取消操作。\n");
				break;
			default:
				printf("无效的选择。\n");
				break;
			}

			found = 1;
			break;
		}
	}

	if (!found) {
		printf("未找到联系人：%s\n", searchName);
	}
}

void dialContact() {
	if (numContacts == 0) {
		printf("通讯录中没有联系人。\n");
		return;
	}

	printf("==== 通讯录 ====\n");
	for (int i = 0; i < numContacts; i++) {
		struct Contact contact = contacts[i];
		printf("%d. %s\n", i + 1, contact.name);
	}
	printf("=================\n");
	printf("请选择要拨号的联系人编号（输入0取消）：");

	int choice;
	scanf("%d", &choice);
	if (choice < 0 || choice > numContacts) {
		printf("无效的选择。\n");
		return;
	}

	if (choice == 0) {
		printf("取消拨号。\n");
		return;
	}

	struct Contact contact = contacts[choice - 1];
	printf("正在拨号给 %s...\n", contact.name);
	printf("号码：");
	for (int i = 0; i < strlen(contact.phone1); i++) {
		if (contact.phone1[i] != '\n') {
			printf("%c", contact.phone1[i]);
			fflush(stdout);
			Sleep(1000);
		}
	}
	printf("\n");
}
void savePhoneToFile() {
	FILE* file = fopen("phone.txt", "w");
	if (file == NULL) {
		printf("无法保存通讯录信息到文件。\n");
		return;
	}

	for (int i = 0; i < numContacts; i++) {
		struct Contact con = contacts[i];
		fprintf(file, "%s\t%s\t%s\t%s\t%s\n",con.name,con.hometown,con.phone1,con.phone2,con.email);
	}

	fclose(file);
	printf("职工信息保存成功。\n");
}

void loadPhoneFromFile() {
	FILE* file = fopen("phone.txt", "r");
	if (file == NULL) {
		printf("无法从文件加载通讯录信息。\n");
		return;
	}

	numContacts = 0;
	while (!feof(file) ) {
		struct Contact con;
		fscanf(file, "%s%s%s%s%s\n", con.name,con.hometown,con.phone1,con.phone2,con.email);
		contacts[numContacts] = con;
		numContacts++;
	}

	fclose(file);
	printf("通讯录信息加载成功。\n");
}
int main() {
	loadPhoneFromFile();
	while (1)
	{
		displayMenu();
		int choice = 0;
		scanf("%d", &choice);
		getchar();
		switch (choice)
		{
		case  1:
			addContact();
			break;
		case  2:
			displayContacts();
			break;
		case  3:
			searchContact();
			break;
		case  4:
			modifyContact();
			break;
		case  5:
			dialContact();
			break;
		case  0:
			printf("退出程序时，自动保存信息到文件中\n");
			savePhoneToFile();
			return;
		default:
			break;
		}
		system("pause");
		system("cls");
	}



	return 0;
}