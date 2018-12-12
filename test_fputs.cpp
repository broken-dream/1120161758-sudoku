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

void make()
{
	for (int row = 0;row < 9;row++) {
		for (int col = 0;col < 9;col++) {
			mp[row][(col * 2 + shift[row]) % 18] = '0' + first_line[col];
		}
	}

	for (int com = 0;com < 36;com++) {
		int idx1 = com / 6;
		int idx2 = com % 6;
		for (int row = 0;row < 3;row++) {
			fputs(mp[row], res);
			//fputc('\n', res);
			//puts(mp[row]);
		}
		for (int row = 0;row < 3;row++) {
			fputs(mp[permutation_change1[idx1][row]], res);
			//fputc('\n', res);
			//puts(mp[permutation_change1[idx1][row]]);
		}
		for (int row = 0;row < 2;row++) {
			fputs(mp[permutation_change2[idx2][row]], res);
			//fputc('\n', res);
			//puts(mp[permutation_change2[idx2][row]]);
		}
		cnt++;
		if (cnt == n) {
			mp[permutation_change2[idx2][2]][17] = '\0';
			fputs(mp[permutation_change2[idx2][2]], res);
			//mp[permutation_change2[idx2][2]][17] = '\n';
			return;
		}
		//puts(mp[permutation_change2[idx2][3]]);
		fputs(mp[permutation_change2[idx2][3]], res);
		fputc('\n',res);
		//putchar('\n');
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

	} while (next_permutation(first_line + 1, first_line + 9));
}
void init()
{
	cnt = 0;
    res = fopen("out.txt", "w");
	//freopen("out.txt", "w+", stdout);
	for (int row = 0;row < 9;row++) {
		for (int col = 0;col < 17;col++) {
			mp[row][col] = ' ';
			mp[row][17] = '\n';
		}
	}
	//mp[9][0] = mp[9][1] = '\n';
}
int main()
{
	DWORD s, e;
	scanf("%u", &n);
	s = GetTickCount();
	init();
	generate();
	e = GetTickCount();
	printf("%ld\n", e - s);
}