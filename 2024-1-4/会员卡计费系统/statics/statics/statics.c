#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_MEMBERS 100
#define VIP_THRESHOLD 1000.0
#define VIP_DISCOUNT 0.9

typedef struct {
	char name[50];
	char id[10];
	float balance;
	float total_spent;
	int is_vip;
} Member;

Member members[MAX_MEMBERS];
int member_count = 0;

int find_member_index_by_id(char* id) {
	for (int i = 0; i < member_count; i++) {
		if (strcmp(members[i].id, id) == 0) {
			return i;
		}
	}
	return -1;
}

/*注册*/
void register_member() {
	if (member_count >= MAX_MEMBERS) {
		printf("会员人数超了，无法注册.\n");
		return;
	}

	Member new_member;
	printf("请输入姓名: ");
	scanf("%s", new_member.name);
	printf("请输入id: ");
	scanf("%s", new_member.id);

	if (find_member_index_by_id(new_member.id) != -1) {
		printf("会员id已经存在无法注册.\n");
		return;
	}

	new_member.balance = 0.0;
	new_member.total_spent = 0.0;
	new_member.is_vip = 0;

	members[member_count++] = new_member;
	printf("新会员注册成功.\n");
}

void modify_member_info() {
	char id[10];
	printf("请输入需要修改的id: ");
	scanf("%s", id);

	int index = find_member_index_by_id(id);
	if (index == -1) {
		printf("会员id不存在.\n");
		return;
	}

	printf("请输入新的名称: ");
	scanf("%s", members[index].name);
	printf("会员信息修改成功.\n");
}

void renew_membership() {
	char id[10];
	float amount;
	printf("请输入会员id: ");
	scanf("%s", id);

	int index = find_member_index_by_id(id);
	if (index == -1) {
		printf("会员不存在.\n");
		return;
	}

	printf("请输入续费的价格: ");
	scanf("%f", &amount);

	members[index].balance += amount;
	printf("已经成功续费新的会费: %.2f\n", members[index].balance);
}

void process_payment() {
	char id[10];
	float amount;
	printf("请输入id: ");
	scanf("%s", id);

	int index = find_member_index_by_id(id);
	if (index == -1) {
		printf("会员id不存在.\n");
		return;
	}

	printf("请输入结算的价格: ");
	scanf("%f", &amount);

	if (members[index].is_vip) {
		amount *= VIP_DISCOUNT;
	}

	if (amount > members[index].balance) {
		printf("卡里余额不足无法结算.\n");
		return;
	}

	members[index].balance -= amount;
	members[index].total_spent += amount;

	if (!members[index].is_vip && members[index].total_spent >= VIP_THRESHOLD) {
		members[index].is_vip = 1;
		printf("消费1000元已经自动升级为会员.\n");
	}

	printf("支付成功. 还剩余额: %.2f\n", members[index].balance);
}

void cancel_membership() {
	char id[10];
	printf("请输入会员id: ");
	scanf("%s", id);

	int index = find_member_index_by_id(id);
	if (index == -1) {
		printf("会员id不存在.\n");
		return;
	}

	printf("会员已经注销. 剩余的余额: %.2f，将会被退回\n", members[index].balance);

	
	for (int i = index; i < member_count - 1; i++) {
		members[i] = members[i + 1];
	}
	member_count--;
}

void display_member_info(Member member) {
	printf("姓名: %s, ID: %s, 余额: %.2f, 累计消费: %.2f, 是否是VIP: %s\n",
		member.name, member.id, member.balance, member.total_spent, member.is_vip ? "Yes" : "No");
}

void sort_and_display_members() {
	
	for (int i = 0; i < member_count - 1; i++) {
		for (int j = 0; j < member_count - i - 1; j++) {
			if (members[j].total_spent < members[j + 1].total_spent) {
				Member temp = members[j];
				members[j] = members[j + 1];
				members[j + 1] = temp;
			}
		}
	}

	for (int i = 0; i < member_count; i++) {
		display_member_info(members[i]);
	}
}

void menu() {
	int choice;
	do {
		printf("\n***** 会员统计系统 *****\n");
		printf("1.注册新会员\n");
		printf("2. 修改会员信息\n");
		printf("3. 续费会员\n");
		printf("4. 结算\n");
		printf("5. 注销会员\n");
		printf("6. 显示信息\n");
		printf("0. 退出\n");
		printf("请输入选项: ");
		scanf("%d", &choice);

		switch (choice) {
		case 1:
			register_member();
			break;
		case 2:
			modify_member_info();
			break;
		case 3:
			renew_membership();
			break;
		case 4:
			process_payment();
			break;
		case 5:
			cancel_membership();
			break;
		case 6:
			sort_and_display_members();
			break;
		case 0:
			printf("退出此系统\n");
			break;
		default:
			printf("输入错误请重新输.\n");
		}
	} while (choice != 0);
}

int main() {
	menu();
	return 0;
}
