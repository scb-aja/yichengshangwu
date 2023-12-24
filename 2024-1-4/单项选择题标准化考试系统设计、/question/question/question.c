#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_QUESTIONS 100
#define MAX_USERS 50
#define MAX_USERNAME 50
#define MAX_PASSWORD 50
#define MAX_QUESTION_LENGTH 256
#define MAX_OPTION_LENGTH 100
#define MAX_ANSWER_LENGTH 10
#define QUESTION_FILE "questions.dat"
#define USER_FILE "users.dat"

typedef struct {
	char question[MAX_QUESTION_LENGTH];
	char options[4][MAX_OPTION_LENGTH];
	char answer;
} Question;

typedef struct {
	char username[MAX_USERNAME];
	char password[MAX_PASSWORD];
	int score;
	int time_taken; // in seconds
} User;

Question questions[MAX_QUESTIONS];
User users[MAX_USERS];
int question_count = 0;
int user_count = 0;

void add_question() {
	if (question_count >= MAX_QUESTIONS) {
		return;
	}

	Question new_question;
	printf("请输入题目: ");
	fgets(new_question.question, MAX_QUESTION_LENGTH, stdin);

	for (int i = 0; i < question_count; i++) {
		if (strcmp(questions[i].question, new_question.question) == 0) {
			printf("题目已经存在，无法录入.\n");
			return;
		}
	}

	printf("请输入四个选项: \n");
	for (int i = 0; i < 4; i++) {
		printf("选项 %d: ", i + 1);
		fgets(new_question.options[i], MAX_OPTION_LENGTH, stdin);
	}

	printf("请输入答案 [A/B/C/D]: ");
	scanf(" %c", &new_question.answer);

	questions[question_count++] = new_question;
	printf("题目添加成功.\n");
}

void take_quiz(User* user) {
	int num_questions;
	printf("请输入抽取的题目: ");
	scanf("%d", &num_questions);

	int score = 0;
	time_t start_time = time(NULL);

	for (int i = 0; i < num_questions; i++) {
		int q_index = rand() % question_count;
		Question q = questions[q_index];

		printf("题目 序号%d: %s\n", i + 1, q.question);
		for (int j = 0; j < 4; j++) {
			printf("%c) %s\n", 'A' + j, q.options[j]);
		}

		char answer;
		printf("请输入答案: ");
		scanf(" %c", &answer);

		if (answer == q.answer) {
			score++;
		}
	}

	time_t end_time = time(NULL);
	user->score = score;
	user->time_taken = (int)difftime(end_time, start_time);

	printf("答题结束. 分数: %d/%d\n", score, num_questions);
}

int find_user_index(char* username) {
	for (int i = 0; i < user_count; i++) {
		if (strcmp(users[i].username, username) == 0) {
			return i;
		}
	}
	return -1;
}

void login_and_take_quiz() {
	char username[MAX_USERNAME], password[MAX_PASSWORD];
	printf("请输入姓名: ");
	scanf("%s", username);
	printf("请输入密码: ");
	scanf("%s", password);

	int user_index = find_user_index(username);
	if (user_index == -1 || strcmp(users[user_index].password, password) != 0) {
		printf("用户名或者密码错误.\n");
		return;
	}

	take_quiz(&users[user_index]);
}

void show_leaderboard() {
	
	for (int i = 0; i < user_count - 1; i++) {
		for (int j = 0; j < user_count - i - 1; j++) {
			if (users[j].score < users[j + 1].score) {
				User temp = users[j];
				users[j] = users[j + 1];
				users[j + 1] = temp;
			}
		}
	}

	printf("排行:\n");
	for (int i = 0; i < user_count; i++) {
		printf("%s - Score: %d, Time: %d seconds\n", users[i].username, users[i].score, users[i].time_taken);
	}
}

void modify_question() {
	char question_to_modify[MAX_QUESTION_LENGTH];
	printf("请输入需要修改的问题: ");
	fgets(question_to_modify, MAX_QUESTION_LENGTH, stdin);

	for (int i = 0; i < question_count; i++) {
		if (strcmp(questions[i].question, question_to_modify) == 0) {
			printf("题目已经找到.\n");
			printf("请输入新的问题: ");
			fgets(questions[i].question, MAX_QUESTION_LENGTH, stdin);

			printf("请输入四个选项: \n");
			for (int j = 0; j < 4; j++) {
				printf("选项 %d: ", j + 1);
				fgets(questions[i].options[j], MAX_OPTION_LENGTH, stdin);
			}

			printf("请输入大难 [A/B/C/D]: ");
			scanf(" %c", &questions[i].answer);
			printf("题目修改完成.\n");
			return;
		}
	}

	printf("题目查不到.\n");
}

void delete_question() {
	char question_to_delete[MAX_QUESTION_LENGTH];
	printf("请输入题目: ");
	fgets(question_to_delete, MAX_QUESTION_LENGTH, stdin);

	for (int i = 0; i < question_count; i++) {
		if (strcmp(questions[i].question, question_to_delete) == 0) {
			for (int j = i; j < question_count - 1; j++) {
				questions[j] = questions[j + 1];
			}
			question_count--;
			printf("题目删除完毕.\n");
			return;
		}
	}

	printf("题目查不到.\n");
}

void extract_questions(int n, Question extracted_questions[]) {
	if (n > question_count) {
		printf("Not enough questions in the database.\n");
		return;
	}

	int extracted_indices[MAX_QUESTIONS] = { 0 };

	for (int i = 0; i < n; i++) {
		int index;
		do {
			index = rand() % question_count;
		} while (extracted_indices[index] == 1);

		extracted_indices[index] = 1;
		extracted_questions[i] = questions[index];
	}
}
/*
*	试题结构
	Question 1
	Option A: Answer 1
	Option B: Answer 2
	Option C: Answer 3
	Option D: Answer 4
	Correct Answer: B
*/
void load_questions() {
	FILE* file = fopen(QUESTION_FILE, "r");
	if (file == NULL) {
		printf("试题不存在!\n");
		return;
	}

	question_count = 0;
	char line[256];
	while (fgets(line, sizeof(line), file)) {
		// 去除末尾可能存在的换行符
		line[strcspn(line, "\n")] = 0;

		strncpy(questions[question_count].question, line, MAX_QUESTION_LENGTH);

		for (int i = 0; i < 4; i++) {
			if (!fgets(line, sizeof(line), file)) break;
			// 去除"Option X: "这部分
			char* option_start = strchr(line, ':') + 2;
			strncpy(questions[question_count].options[i], option_start, MAX_OPTION_LENGTH);
		}

		if (!fgets(line, sizeof(line), file)) 
			break;
		// 获取正确答案，假设格式是"Correct Answer: X"
		char* answer_start = strchr(line, ':') + 2;
		questions[question_count].answer = answer_start[0];

		question_count++;
	}

	fclose(file);
	printf("成功正在入试题.\n", question_count);
}

void show_menu() {
	int choice;
	do {
		printf("1. 添加问题\n");
		printf("2. 修改问题\n");
		printf("3. 删除问题\n");
		printf("4. 答题\n");
		printf("5. 排行榜\n");
		printf("0. 退出\n");
		printf("请输入选项: ");
		scanf("%d", &choice);

		switch (choice) {
		case 1:
			add_question();
			break;
		case 2:
			modify_question();
			break;
		case 3:
			delete_question();
			break;
		case 4:
			login_and_take_quiz();
			break;
		case 5:
			show_leaderboard();
			break;
		case 0:
			printf("Exiting...\n");
			break;
		default:
			printf("输入错误，请重新输入.\n");
		}
	} while (choice != 0);
}

int main() {
	load_questions();
	show_menu();
	return 0;
}
