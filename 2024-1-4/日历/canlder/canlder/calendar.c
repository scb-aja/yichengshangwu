#define  _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<time.h>
void menu();
void year_calendar();
void year_month_calendar();
void year_month_day_calendar();
int main()
{
	int choice;
	menu();
	printf("请选择你要的日历服务序号：");
	scanf("%d", &choice);
	switch (choice)
	{
	case 1:year_calendar(); break;
	case 2:year_month_calendar(); break;
	case 3:year_month_day_calendar(); break;
	}
	getchar(); getchar(); getchar(); getchar();
	return 0;
}


void menu()
{
	printf("*****************************************************************\n");
	printf("                       欢迎来到日历查询系统                      \n");
	printf("                          1:查询某年日历                         \n");
	printf("                          2:查询某年某月的日历                   \n");
	printf("                          3:查询某年月日的日历信息               \n");
	printf("*****************************************************************\n");
}


void year_calendar()
{
	int year, day, i, j, k, n, m, q, month_one_weekday[13];//day--到今年一月一日前共多少天； month_one_weekday[13]--每个月1号是星期几；
	//m:每个月已输出多少天；  n-每一年的天数;  q: 每个月一日之前需要输出的空白天数。
	int month_day[13];  //month_day[13]---查询当年每月共计多少天。
	//year_month_one_day[13]---查询从0年0月到查询当年每月第一天共计多少天
	printf("请输入你要查询日历的年份：");
	scanf("%d", &year);
	day = 0;
	for (i = 1; i <= year - 1; i++)
	{
		if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))
			n = 366;
		else n = 365;
		day = day + n;
	}
	month_day[0] = 0;
	for (i = 1; i <= 12; i++)
	{
		switch (i)
		{
		case 1:case 3:case 5:case 7:
		case 8:case 10:case 12:       month_day[i] = 31; break;
		case 4:case 6:case 9:case 11: month_day[i] = 30; break;
		case 2:if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))
			month_day[i] = 29;
			  else month_day[i] = 28;
			break;
		}
		day = day + month_day[i - 1];  //day: 第i月1日前，共计的天数；
		if ((day + 1) % 7 == 0)  month_one_weekday[i] = 7;
		else month_one_weekday[i] = (day + 1) % 7;//month_one_weekday[i]:第i个月的第一天是星期几


	}
	for (i = 1; i <= 12; i++)//每循环一次输出一个月的日历
	{
		printf("\n\n");
		printf("\n%2i月：Sun\tMon\tTue\tWed\tThur\tFri\tSat\n", i);
		for (j = 1, m = 0; j <= month_day[i]; j++)//j:每个月的每一天；  m：已经输出的天数
		{


			if (j == 1)   //第一天前面需要空多少天
			{
				printf("     ");
				q = month_one_weekday[i] - 1;
				for (k = 1; k <= q; k++)
					printf("\t");
				printf("\t%d\t", j); m = q + 1;
			}
			else { printf("%d\t", j); m++; }
			if (m % 7 == 0)
				printf("\n       ");
		}

	}




}


void year_month_calendar()
{
	int year, month, day = 0;
	int i, j, k, n, m, q;
	int month_day[13], month_one_weekday[13];
	printf("\n请输入要查询日历的年月：");
	scanf("%d%d", &year, &month);
	day = 0;
	for (i = 1; i <= year - 1; i++)
	{
		if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))
			n = 366;
		else n = 365;
		day = day + n;
	}
	month_day[0] = 0;
	for (i = 1; i <= 12; i++)
	{
		switch (i)
		{
		case 1:case 3:case 5:case 7:
		case 8:case 10:case 12:       month_day[i] = 31; break;
		case 4:case 6:case 9:case 11: month_day[i] = 30; break;
		case 2:if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))
			month_day[i] = 29;
			  else month_day[i] = 28;
			break;
		}
		day = day + month_day[i - 1];  //day: 第i月1日前，共计的天数；
		if ((day + 1) % 7 == 0)  month_one_weekday[i] = 7;
		else month_one_weekday[i] = (day + 1) % 7;//month_one_weekday[i]:第i个月的第一天是星期几
	}
	printf("%d年的第%d月日历是:\n", year, month);
	printf("要查询的当月共计多少天：%d\n", month_day[month]);
	printf("\n%2i月：Sun\tMon\tTue\tWed\tThur\tFri\tSat\n", month);
	for (j = 1, m = 0; j <= month_day[month]; j++)//j:每个月的每一天；  m：已经输出的天数
	{
		if (j == 1)   //第一天前面需要空多少天
		{
			printf("     ");
			q = month_one_weekday[month] - 1;
			for (k = 1; k <= q; k++)
				printf("\t");
			printf("\t%d\t", j); m = q + 1;
		}
		else { printf("%d\t", j); m++; }
		if (m % 7 == 0)
			printf("\n       ");
	}
}




void year_month_day_calendar()  //输入年月日，输出距今天还有多少天，星期几，是否是公历节日。
{
	int year, month, dayy, day, day1, day2, weekday, flag, n1, n2, n, i;   //n--距离今天还有多少天，dayy--输入的day
	//n1--输入的日期距离公元1年1月1日的天数
	//n2--当前系统日期距离公元1年1月1日的天数
	int month_day[13];
	struct tm* local;
	time_t t;
	printf("\n请输入查询的年月日：");
	scanf("%d%d%d", &year, &month, &dayy);
	printf("输入的日期是：%d年%d月%d日！", year, month, dayy);
	if ((month == 1 && dayy == 1) || (month == 5 && dayy == 1) || (month == 10 && dayy == 1))
		printf("输入日期是法定假日！\n");
	else printf("输入日期不是法定假日！\n");


	day = 0;
	for (i = 1; i <= year - 1; i++)
	{
		if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))
			n = 366;
		else n = 365;
		day = day + n;
	}
	day1 = day;
	month_day[0] = 0;
	for (i = 1; i <= 12; i++)
	{
		switch (i)
		{
		case 1:case 3:case 5:case 7:
		case 8:case 10:case 12:       month_day[i] = 31; break;
		case 4:case 6:case 9:case 11: month_day[i] = 30; break;
		case 2:if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))
			month_day[i] = 29;
			  else month_day[i] = 28;
			break;
		}
	}
	for (i = 1, n1 = 0; i <= month - 1; i++)
		day1 = day1 + month_day[i];
	day1 = day1 + dayy;
	n1 = day1;          //n1--公元1年1月1日，到输入日期的天数；


	t = time(NULL);
	local = localtime(&t);
	year = local->tm_year + 1900;
	month = local->tm_mon + 1;
	dayy = local->tm_mday;
	printf("\n今天的日期是：%d年%d月%d日。\n", year, month, dayy);


	day2 = day;
	for (i = 1; i <= 12; i++)
	{
		switch (i)
		{
		case 1:case 3:case 5:case 7:
		case 8:case 10:case 12:       month_day[i] = 31; break;
		case 4:case 6:case 9:case 11: month_day[i] = 30; break;
		case 2:if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))
			month_day[i] = 29;
			  else month_day[i] = 28;
			break;
		}
	}
	for (i = 1, n2 = 0; i <= month - 1; i++)
		day2 = day2 + month_day[i];
	day2 = day2 + dayy;
	n2 = day2;          //n2--公元1年1月1日，到当前日期的天数；


	printf("输入日期距离当前系统日期还有%d天！\n", n2 - n1);
	if ((month == 1 && dayy == 1) || (month == 5 && dayy == 1) || (month == 10 && dayy == 1))
		printf("当前日期是法定假日！\n");
	else printf("当前日期不是法定假日！\n");


}