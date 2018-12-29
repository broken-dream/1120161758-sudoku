#include<cstdio>
#include<cstring>
#include<iostream>
#include<ctime>
#include<algorithm>
#include<Windows.h>
#include<Mmsystem.h>
using namespace std;
char first_line[10] = { 4,1,2,3,5,6,7,8,9 };
unsigned int shift[9] = { 0,6,12,2,8,14,4,10,16 };
unsigned int permutation_change1[6][3] = { { 3,4,5 },{ 3,5,4 },{ 4,3,5 },{ 4,5,3 },{ 5,3,4 },{ 5,4,3 } };
unsigned int permutation_change2[6][3] = { { 6,7,8 },{ 6,8,7 },{ 7,6,8 },{ 7,8,6 },{ 8,6,7 },{ 8,7,6 } };
char mp[10][20];
char temp[163000005];
unsigned int cnt;
unsigned int n;
FILE *res;
bool flag_gene;
char visit_squard[3][3][11] = { 0 };
char visit_row[18][11] = { 0 };
char visit_col[18][11] = { 0 };
char init_exist[18][18] = { 0 };
char store_blank[3];
bool flag_solve;
bool flag_blank;
int total = 0;
int error_type = 0;
bool judge(char row, char col, char num) {
	if (visit_row[row][num] ||
		visit_col[col][num] ||
		visit_squard[row / 3][col / 6][num]) {
		return 0;
	}
	return 1;
}
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

void make()
{
	for (int row = 0;row < 9;row++) {
		for (int col = 0;col < 9;col++) {
			mp[row][(col * 2 + shift[row]) % 18] = '0' + first_line[col];
		}
	}

	for (int out = 0;out < 2;out++) {
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
}
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

void init_for_solve()
{
	cnt = 0;
	flag_blank = 0;
	res = fopen("sudokures.txt", "w+");
	//freopen("out.txt", "w+", stdout);
	for (int row = 0;row < 9;row++) {
		for (int col = 0;col < 17;col++) {
			mp[row][col] = ' ';
			mp[row][17] = '\0';
		}
	}
}

void ctrl_module(int argc, char *argv[])
{
	//printf("%s\n", argv[2]);
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
		printf("开始生成...\n");
		DWORD s, e;
		n = atoi(argv[2]);
		s = GetTickCount();
		init_for_generate();
		generate();
		fwrite(temp, sizeof(char), strlen(temp), res);
		e = GetTickCount();
		printf("结束\n");
		printf("生成用时：%ld\n", e - s);
		fclose(res);
	}
	else if (argc == 3 && strlen(argv[1]) == 2 && (argv[1][0] == '-'&&argv[1][1] == 's')) {
		FILE* input = fopen(argv[2], "r");
		if (input == NULL) {
			error_type = 1;
			printf("error:%d,file open faild\n", error_type);
			return;
		}
		DWORD global_s, global_e;
		global_s = GetTickCount();

		init_for_solve();
		unsigned int cnt_num = 0;
		unsigned int pos = 0;
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
		global_e = GetTickCount();
		printf("求解时间：%ld\n", total);
		printf("全部时间：%ld\n", global_e - global_s);
	}
	else {
		error_type = 2;
		printf("error:%d,illegal parameter\n", error_type);
	}
}
int main(int argc, char* argv[])
{
	printf("%s\n", argv[2]);
	DWORD s, e;
	s = GetTickCount();
	ctrl_module(argc, argv);
	e = GetTickCount();
	printf("全局用时：%ld\n", e - s);
}