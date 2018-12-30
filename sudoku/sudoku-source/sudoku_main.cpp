#include<cstdio>
#include<cstring>
#include<iostream>
#include<ctime>
#include<algorithm>
#include<Windows.h>
#include<Mmsystem.h>
using namespace std;
char first_line[10] = { 4,1,2,3,5,6,7,8,9 };              //字典序最小的第一行
unsigned int shift[9] = { 0,6,12,2,8,14,4,10,16 };        //位移量，因为考虑空格所以都进行了乘2
unsigned int permutation_change1[6][3] = { { 3,4,5 },{ 3,5,4 },{ 4,3,5 },{ 4,5,3 },{ 5,3,4 },{ 5,4,3 } };     //中间三行的行变换排列
unsigned int permutation_change2[6][3] = { { 6,7,8 },{ 6,8,7 },{ 7,6,8 },{ 7,8,6 },{ 8,6,7 },{ 8,7,6 } };	  //最后三行的行变换排列
char temp[163000005];		//缓冲区 用来存储结果然后一次性输出
char mp[10][20];			//数独矩阵，因为考虑空格所以列数进行了乘2
unsigned int cnt;			//生成计数
unsigned int n;				//要求生成的个数
FILE *res;					//指向结果文件的指针
bool flag_gene;				//是否完成生成，完成为1，未完成为0
char visit_squard[3][3][11] = { 0 };			//记录每个小矩形内数字出现情况
char visit_row[18][11] = { 0 };					//记录每行数字出现情况
char visit_col[18][11] = { 0 };					//记录每列数字出现情况
char init_exist[18][18] = { 0 };				//记录初始时存在的数字
char store_blank[3];
bool flag_solve;								//是否完成求解，完成为1，未完成为0
bool flag_blank;
int total = 0;
int error_type = 0;								//指示错误类型，0为正常，1表示文件的打开失败，2表示
												//参数格式错误，3表示针对生成第三个参数格式不合法

/**************************************************/
/*名称：judge
/*描述：判断是否符合数独规则
/*参数：
参数1：参数名称 row、参数类型 char、参数含义：当前行数
参数2：参数名称 col、参数类型 char、参数含义：当前列数
参数3：参数名称 num、参数类型 char、参数含义：欲填充的数字
/*返回值：bool型，1表示可以填，0表示不可以
/***************************************************/
bool judge(char row, char col, char num) {
	if (visit_row[row][num] ||
		visit_col[col][num] ||
		visit_squard[row / 3][col / 6][num]) {
		return 0;
	}
	return 1;
}
/**************************************************/
/*名称：check_n
/*描述：判断生成终局的个数是否合法
/*参数：
参数1：参数名称 num、参数类型 char*、参数含义：表示个数的字符串
/*返回值：bool型，1表示合法，0表示不合法
/***************************************************/
bool check_n(char *num)
{
	int len = strlen(num);
	for (int i = 0;i < len;i++) {
		if (num[i]<'0' || num[i]>'9') {
			return false;
		}
	}
	return true;
}
/**************************************************/
/*名称：solve
/*描述：递归求解数独
/*参数：
参数1：参数名称 cur_cnt、参数类型 unsigned int、参数含义：表示当前填写第几个数
/*返回值：无
/***************************************************/
void solve(unsigned int cur_cnt)
{
	if (cur_cnt == 162) {
		flag_solve = 1;
	}
	if (flag_solve) {
		return;
	}
	char row = cur_cnt / 18;
	char col = cur_cnt % 18;
	if (init_exist[row][col]) {
		solve(cur_cnt + 2);
	}
	else {
		for (unsigned int i = 1;i <= 9;i++) {
			if (flag_solve) {
				return;
			}
			if (judge(row, col, i)) {
				mp[row][col] = i;
				visit_row[row][i] = 1;
				visit_col[col][i] = 1;
				visit_squard[row / 3][col / 6][i] = 1;
				solve(cur_cnt + 2);
				visit_row[row][i] = 0;
				visit_col[col][i] = 0;
				visit_squard[row / 3][col / 6][i] = 0;
			}
		}
	}
}
/**************************************************/
/*名称：print_res
/*描述：输出数独求解结果
/*参数：无
/*返回值：无
/***************************************************/
void print_res()
{
	for (int i = 0;i < 9;i++) {
		for (int j = 0;j < 18;j += 2) {
			mp[i][j] += '0';
		}
	}
	for (int i = 0;i < 8;i++) {
		fputs(mp[i], res);
	}
	fputs(mp[8], res);
}
/**************************************************/
/*名称：make
/*描述：生成一组数独终局
/*参数：无
/*返回值：无
/***************************************************/
void make()
{
	for (int row = 0;row < 9;row++) {
		for (int col = 0;col < 9;col++) {
			mp[row][(col * 2 + shift[row]) % 18] = '0' + first_line[col];
		}
	}

	for (int com = 0;com < 36;com++) {
		int cur_cnt = 0;
		int idx1 = com / 6;
		int idx2 = com % 6;
		for (int row = 0;row < 3;row++) {
			strcpy(temp + cnt * 163 + cur_cnt * 18, mp[row]);
			cur_cnt++;
		}
		for (int row = 0;row < 3;row++) {
			strcpy(temp + cnt * 163 + cur_cnt * 18, mp[permutation_change1[idx1][row]]);
			cur_cnt++;
		}
		for (int row = 0;row < 2;row++) {
			strcpy(temp + cnt * 163 + cur_cnt * 18, mp[permutation_change2[idx2][row]]);
			cur_cnt++;
		}
		cnt++;
		if (cnt == n) {
			mp[permutation_change2[idx2][2]][17] = '\0';
			strcpy(temp + (cnt - 1) * 163 + cur_cnt * 18, mp[permutation_change2[idx2][2]]);
			return;
		}
		strcpy(temp + (cnt - 1) * 163 + cur_cnt * 18, mp[permutation_change2[idx2][2]]);
		temp[(cnt - 1) * 163 + (cur_cnt + 1) * 18] = '\n';
	}
}
/**************************************************/
/*名称：generate
/*描述：更新第一行的排列并调用make
/*参数：无
/*返回值：无
/***************************************************/
void generate()
{
	do {
		if (cnt == n) {
			return;
		}
		for (int col = 0;col < 9;col++) {
			mp[0][col * 2] = first_line[col];
		}
		make();
		//printf("%d\n", cnt);
		//printf("%d\n", strlen(temp));
	} while (next_permutation(first_line + 1, first_line + 9));

}
/**************************************************/
/*名称：init_for_generate
/*描述：初始化生成相关的变量
/*参数：无
/*返回值：无
/***************************************************/
void init_for_generate()
{
	cnt = 0;

	for (int row = 0;row < 9;row++) {
		for (int col = 0;col < 17;col++) {
			mp[row][col] = ' ';
			mp[row][17] = '\n';
			mp[row][18] = '\0';
		}
	}
}
/**************************************************/
/*名称：init_for_solve
/*描述：初始化求解相关的变量
/*参数：无
/*返回值：无
/***************************************************/
void init_for_solve()
{
	cnt = 0;
	flag_blank = 0;
	res = fopen("sudokures.txt", "w+");
	for (int row = 0;row < 9;row++) {
		for (int col = 0;col < 17;col++) {
			mp[row][col] = ' ';
			mp[row][17] = '\0';
		}
	}
}
/**************************************************/
/*名称：ctrl_gene
/*描述：生成的主控制模块
/*参数：无
/*返回值：无
/***************************************************/
void ctrl_gene()
{
	printf("开始生成...\n");
	DWORD s, e;
	s = GetTickCount();
	init_for_generate();
	generate();
	fwrite(temp, sizeof(char), strlen(temp), res);
	e = GetTickCount();
	printf("结束\n");
	printf("生成用时：%ldms\n", e - s);
	fclose(res);
}
/**************************************************/
/*名称：ctrl_solve
/*描述：求解的主控制模块
/*参数：
参数1：参数名称 input、参数类型 FILE*、参数含义：输入的数独问题
/*返回值：无
/***************************************************/
void ctrl_solve(FILE *input)
{
	init_for_solve();
	unsigned int cnt_num = 0;
	unsigned int pos = 0;
	printf("开始求解...\n");
	while (fgets(mp[0], 19, input) != NULL) {
		for (int i = 1;i < 9;i++) {
			fgets(mp[i], 19, input);
		}
		for (int i = 0;i < 9;i++) {
			for (int j = 0;j < 18;j += 2) {
				if (mp[i][j] != '0') {
					mp[i][j] -= '0';
					visit_row[i][mp[i][j]] = 1;
					visit_col[j][mp[i][j]] = 1;
					visit_squard[i / 3][(j / 6)][mp[i][j]] = 1;
					init_exist[i][j] = 1;
				}
			}
		}
		mp[8][17] = '\0';
		cnt = 0;
		flag_solve = 0;
		pos = 0;
		cnt_num = 0;
		DWORD s, e;
		s = GetTickCount();
		solve(0);
		e = GetTickCount();
		total += e - s;
		memset(visit_col, 0, sizeof(visit_col));
		memset(visit_row, 0, sizeof(visit_row));
		memset(visit_squard, 0, sizeof(visit_squard));
		memset(init_exist, 0, sizeof(init_exist));
		if (!flag_blank) {
			flag_blank = 1;
		}
		else {
			fputs("\n\n", res);
		}
		print_res();
		fgets(store_blank, 2, input);

	}
	fclose(input);
	fclose(res);
	printf("结束\n");
	printf("求解时间：%ldms\n", total);
}
/**************************************************/
/*名称：ctrl_module
/*描述：整个程序的主控模块
/*参数：
参数1：参数名称 argc、参数类型 int、参数含义：参数个数
参数2：参数名称 argv、参数类型 *char[]、参数含义：命令行传入的参数
/*返回值：无
/***************************************************/
void ctrl_module(int argc, char *argv[])
{
	if (argc == 3 && strlen(argv[1]) == 2 && (argv[1][0] == '-'&&argv[1][1] == 'c')) {
		res = fopen("sudoku.txt", "w");
		if (res == NULL) {
			error_type = 1;
			printf("error:%d,file open faild\n", error_type);
			return;
		}
		if (!check_n(argv[2])) {
			error_type = 3;
			printf("error:%d,you should input a positive integer\n", error_type);
			return;
		}
		n = atoi(argv[2]);
		ctrl_gene();
	}
	else if (argc == 3 && strlen(argv[1]) == 2 && (argv[1][0] == '-'&&argv[1][1] == 's')) {
		FILE* input = fopen(argv[2], "r");
		if (input == NULL) {
			error_type = 1;
			printf("error:%d,file open faild\n", error_type);
			return;
		}
		ctrl_solve(input);
	}
	else {
		error_type = 2;
		printf("error:%d,illegal parameter\n", error_type);
	}
}
int main(int argc, char* argv[])
{
	DWORD s, e;
	s = GetTickCount();
	ctrl_module(argc, argv);
	e = GetTickCount();
	printf("全局用时：%ldms\n", e - s);
}