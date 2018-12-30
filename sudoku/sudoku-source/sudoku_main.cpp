#include<cstdio>
#include<cstring>
#include<iostream>
#include<ctime>
#include<algorithm>
#include<Windows.h>
#include<Mmsystem.h>
using namespace std;
char first_line[10] = { 4,1,2,3,5,6,7,8,9 };              //�ֵ�����С�ĵ�һ��
unsigned int shift[9] = { 0,6,12,2,8,14,4,10,16 };        //λ��������Ϊ���ǿո����Զ������˳�2
unsigned int permutation_change1[6][3] = { { 3,4,5 },{ 3,5,4 },{ 4,3,5 },{ 4,5,3 },{ 5,3,4 },{ 5,4,3 } };     //�м����е��б任����
unsigned int permutation_change2[6][3] = { { 6,7,8 },{ 6,8,7 },{ 7,6,8 },{ 7,8,6 },{ 8,6,7 },{ 8,7,6 } };	  //������е��б任����
char temp[163000005];		//������ �����洢���Ȼ��һ�������
char mp[10][20];			//����������Ϊ���ǿո��������������˳�2
unsigned int cnt;			//���ɼ���
unsigned int n;				//Ҫ�����ɵĸ���
FILE *res;					//ָ�����ļ���ָ��
bool flag_gene;				//�Ƿ�������ɣ����Ϊ1��δ���Ϊ0
char visit_squard[3][3][11] = { 0 };			//��¼ÿ��С���������ֳ������
char visit_row[18][11] = { 0 };					//��¼ÿ�����ֳ������
char visit_col[18][11] = { 0 };					//��¼ÿ�����ֳ������
char init_exist[18][18] = { 0 };				//��¼��ʼʱ���ڵ�����
char store_blank[3];
bool flag_solve;								//�Ƿ������⣬���Ϊ1��δ���Ϊ0
bool flag_blank;
int total = 0;
int error_type = 0;								//ָʾ�������ͣ�0Ϊ������1��ʾ�ļ��Ĵ�ʧ�ܣ�2��ʾ
												//������ʽ����3��ʾ������ɵ�����������ʽ���Ϸ�

/**************************************************/
/*���ƣ�judge
/*�������ж��Ƿ������������
/*������
����1���������� row���������� char���������壺��ǰ����
����2���������� col���������� char���������壺��ǰ����
����3���������� num���������� char���������壺����������
/*����ֵ��bool�ͣ�1��ʾ�����0��ʾ������
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
/*���ƣ�check_n
/*�������ж������վֵĸ����Ƿ�Ϸ�
/*������
����1���������� num���������� char*���������壺��ʾ�������ַ���
/*����ֵ��bool�ͣ�1��ʾ�Ϸ���0��ʾ���Ϸ�
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
/*���ƣ�solve
/*�������ݹ��������
/*������
����1���������� cur_cnt���������� unsigned int���������壺��ʾ��ǰ��д�ڼ�����
/*����ֵ����
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
/*���ƣ�print_res
/*������������������
/*��������
/*����ֵ����
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
/*���ƣ�make
/*����������һ�������վ�
/*��������
/*����ֵ����
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
/*���ƣ�generate
/*���������µ�һ�е����в�����make
/*��������
/*����ֵ����
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
/*���ƣ�init_for_generate
/*��������ʼ��������صı���
/*��������
/*����ֵ����
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
/*���ƣ�init_for_solve
/*��������ʼ�������صı���
/*��������
/*����ֵ����
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
/*���ƣ�ctrl_gene
/*���������ɵ�������ģ��
/*��������
/*����ֵ����
/***************************************************/
void ctrl_gene()
{
	printf("��ʼ����...\n");
	DWORD s, e;
	s = GetTickCount();
	init_for_generate();
	generate();
	fwrite(temp, sizeof(char), strlen(temp), res);
	e = GetTickCount();
	printf("����\n");
	printf("������ʱ��%ldms\n", e - s);
	fclose(res);
}
/**************************************************/
/*���ƣ�ctrl_solve
/*����������������ģ��
/*������
����1���������� input���������� FILE*���������壺�������������
/*����ֵ����
/***************************************************/
void ctrl_solve(FILE *input)
{
	init_for_solve();
	unsigned int cnt_num = 0;
	unsigned int pos = 0;
	printf("��ʼ���...\n");
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
	printf("����\n");
	printf("���ʱ�䣺%ldms\n", total);
}
/**************************************************/
/*���ƣ�ctrl_module
/*�������������������ģ��
/*������
����1���������� argc���������� int���������壺��������
����2���������� argv���������� *char[]���������壺�����д���Ĳ���
/*����ֵ����
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
	printf("ȫ����ʱ��%ldms\n", e - s);
}