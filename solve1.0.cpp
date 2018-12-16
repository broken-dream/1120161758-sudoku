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
unsigned int cnt;
unsigned int n;
FILE *res;
bool falg_gene;
char visit_squard[3][3][11] = { 0 };
char visit_row[18][11] = { 0 };
char visit_col[18][11] = { 0 };
char init_exist[18][18] = { 0 };
bool flag;
bool flag_blank;
int total = 0;
bool judge(char row, char col, char num) {
	if (visit_row[row][num] ||
		visit_col[col][num] ||
		visit_squard[row / 3][col / 6][num]) {
		return 0;
	}
	/*int a, c, b;
	if (visit_row[row][num]) a = 1;
	else a = 0;
	if (visit_col[col][num]) b = 1;
	else b = 0;
	if (visit_squard[row / 3][col / 6][num]) c = 1;
	else c = 0;
	if (a || b || c) return 0;*/
	return 1;
}
void solve(unsigned int cur_cnt)
{
	if (cur_cnt == 162) {
		flag = 1;
	}
	if (flag) {
		return;
	}
	char row = cur_cnt / 18;
	char col = cur_cnt % 18;
	if (init_exist[row][col]) {
		solve(cur_cnt + 2);
	}
	else{
		for (unsigned int i = 1;i <= 9;i++) {
			if (flag) {
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
		fputc('\n', res);
	}
	fputs(mp[8], res);
}
void init()
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
int main()
{
	//FILE* input = fopen("in.txt", "r");
	FILE* input = fopen("problem.txt", "r");
	init();
	if (input == NULL) {
		printf("Reading input error!\n");
		return 0;
	}
	unsigned int cnt_num = 0;
	unsigned int pos = 0;
	unsigned int cur;
	while (fscanf(input, "%d", &cur) != EOF) {
		int pos = 0;
		char row = pos / 18;
		char col = pos % 18;
		if (cur) {
			init_exist[row][col] = 1;
			//printf("%d %d\n", row, col);
		}
		else cur += ' ';
		mp[0][0] = cur;
		visit_row[row][cur] = 1;
		visit_col[col][cur] = 1;
		visit_squard[row / 3][(col / 6)][cur] = 1;
		pos += 2;
		for (int i = 0;i < 80;i++) {
			fscanf(input, "%d", &cur);
			row = pos / 18;
			col = pos % 18;
			visit_row[row][cur] = 1;
			visit_col[col][cur] = 1;
			visit_squard[row / 3][(col / 6)][cur] = 1;
			if (cur == 0) cur += ' ';
			else {
				init_exist[row][col] = 1;
				//printf("%d %d\n", row, col);
			}
			mp[row][col] = cur;
			pos += 2;
		}
		cnt = 0;
		flag = 0;
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
		memset(mp, 0, sizeof(mp));
		for (int row = 0;row < 9;row++) {
			for (int col = 0;col < 17;col++) {
				mp[row][col] = ' ';
				mp[row][17] = '\0';
			}
		}
		/*	if (cur) {
				char row = pos / 18;
				char col = pos % 18;
				mp[row][col] = cur;
				visit_row[row][cur] = 1;
				visit_col[col][cur] = 1;
				visit_squard[row / 3][(col / 6)][cur] = 1;
				init_exist[row][col] = 1;
			}
			cnt_num++;
			pos += 2;
			if (cnt_num == 81) {
				cnt = 0;
				flag = 0;
				pos = 0;
				cnt_num = 0;
				solve(0);
				memset(visit_col, 0, sizeof(visit_col));
				memset(visit_row, 0, sizeof(visit_row));
				memset(visit_squard, 0, sizeof(visit_squard));
				if (!flag_blank) {
					flag_blank = 1;
				}
				else {
					fputs("\n\n", res);
				}
				print_res();
				memset(mp, 0, sizeof(mp));
				for (int row = 0;row < 9;row++) {
					for (int col = 0;col < 17;col++) {
						mp[row][col] = ' ';
						mp[row][17] = '\0';
					}
				}
			}
		}*/
	}
	fclose(input);
	fclose(res);
	printf("%ld\n", total);
}
