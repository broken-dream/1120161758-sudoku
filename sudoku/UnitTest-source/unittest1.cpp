#include "stdafx.h"
#include "CppUnitTest.h"
#include<cstring>
#include "../sudoku/sudoku_main.cpp"
//#include "../软工项目/main_nowarning.cpp"
//#include "../软工项目/main-unittest.cpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace sudokuunittest
{
	TEST_CLASS(UnitTest1)
	{
	private:
		int mp[9][9] = { 0 };
		int visit_row[9][9] = { 0 };
		int visit_col[9][9] = { 0 };
		int visit_sq[3][3][9] = { 0 };
		/*char mp[20][20] = {
		{'4',' ', '1', ' ', '2', ' ', '3', ' ', '5', ' ', '6', ' ', '7', ' ', '8', ' ', '9', '\n', '\0'},
		{ '7',' ', '8', ' ', '9', ' ', '4', ' ', '1', ' ', '2', ' ', '3', ' ', '5', ' ', '6', '\n', '\0' },
		{ '3',' ', '5', ' ', '6', ' ', '7', ' ', '8', ' ', '9', ' ', '4', ' ', '1', ' ', '2', '\n', '\0' },
		{ '9',' ', '4', ' ', '1', ' ', '2', ' ', '3', ' ', '5', ' ', '6', ' ', '7', ' ', '8', '\n', '\0' },
		{ '6',' ', '7', ' ', '8', ' ', '9', ' ', '4', ' ', '1', ' ', '2', ' ', '3', ' ', '5', '\n', '\0' },
		{ '2',' ', '3', ' ', '5', ' ', '6', ' ', '7', ' ', '8', ' ', '9', ' ', '4', ' ', '1', '\n', '\0' },
		{ '8',' ', '9', ' ', '4', ' ', '1', ' ', '2', ' ', '3', ' ', '5', ' ', '6', ' ', '7', '\n', '\0' },
		{ '5',' ', '6', ' ', '7', ' ', '8', ' ', '9', ' ', '4', ' ', '1', ' ', '2', ' ', '3', '\n', '\0' },
		{ '1',' ', '2', ' ', '3', ' ', '5', ' ', '6', ' ', '7', ' ', '8', ' ', '9', ' ', '4', '\n', '\0' },
		};*/
	public:
		/*
		error_type取值说明：
		0：正确
		1：文件打开失败
		2：参数格式不合法
		3：对于生成，第三个参数不合法
		*/
		TEST_METHOD(TestPara1)
		{
			// TODO: 在此输入测试代码
			char *argv[3];
			argv[0] = "软工项目.exe";
			argv[1] = "abc";
			argv[2] = "100";
			ctrl_module(3, argv);
			Assert::AreEqual(error_type, 2);
		}
		TEST_METHOD(TestPara2)
		{
			// TODO: 在此输入测试代码
			char *argv[3];
			argv[0] = "软工项目.exe";
			argv[1] = "-c";
			argv[2] = "-100";
			ctrl_module(3, argv);
			Assert::AreEqual(error_type, 3);
		}
		TEST_METHOD(TestPara3)
		{
			// TODO: 在此输入测试代码
			char *argv[3];
			argv[0] = "软工项目.exe";
			argv[1] = "-c";
			argv[2] = "1000.1";
			ctrl_module(3, argv);
			Assert::AreEqual(error_type, 3);
		}
		TEST_METHOD(TestPara4)
		{
			// TODO: 在此输入测试代码
			char *argv[3];
			argv[0] = "软工项目.exe";
			argv[1] = "-c";
			argv[2] = "abc";
			ctrl_module(3, argv);
			Assert::AreEqual(error_type, 3);
		}
		TEST_METHOD(TestPara5)
		{
			// TODO: 在此输入测试代码
			char *argv[3];
			argv[0] = "软工项目.exe";
			argv[1] = "-s";
			argv[2] = "sfa";
			ctrl_module(3, argv);
			Assert::AreEqual(error_type, 1);
		}
		TEST_METHOD(TestPara6)
		{
			// TODO: 在此输入测试代码
			char *argv[3];
			argv[0] = "软工项目.exe";
			argv[1] = "ab";
			argv[2] = "100";
			ctrl_module(3, argv);
			Assert::AreEqual(error_type, 2);
		}
		TEST_METHOD(TestPara7)
		{
			// TODO: 在此输入测试代码
			char *argv[4];
			argv[0] = "软工项目.exe";
			argv[1] = "-c";
			argv[2] = "100";
			argv[3] = "kkkkk";
			ctrl_module(4, argv);
			Assert::AreEqual(error_type, 2);
		}
		TEST_METHOD(TestPara8)
		{
			// TODO: 在此输入测试代码
			char *argv[2];
			argv[0] = "软工项目.exe";
			argv[1] = "-c";
			ctrl_module(2, argv);
			Assert::AreEqual(error_type, 2);
		}
		TEST_METHOD(TestGenerate)
		{
			char *argv[3];
			argv[0] = "软工项目.exe";
			argv[1] = "-c";
			argv[2] = "10";
			ctrl_module(3, argv);
			FILE* input = fopen("../Debug/sudoku.txt", "r");
			Assert::AreEqual(check(input), 0);
		}
		TEST_METHOD(TestSolve)
		{
			char *argv[3];
			argv[0] = "软工项目.exe";
			argv[1] = "-s";
			argv[2] = "../Debug/ques.txt";
			ctrl_module(3, argv);
			FILE* input = fopen("../Debug/sudokures.txt", "r");
			Assert::AreEqual(check(input), 0);
		}
		int judge_unit(int row, int col, int num) {
			if (visit_row[row][num] ||
				visit_col[col][num] ||
				visit_sq[row / 3][col / 3][num])
				return 1;
			return 0;
		}
		int check(FILE* input)
		{
			//freopen("checkres.txt", "w", stdout);
			int cnt = 0;
			int error_flag = 0;
			while (fscanf(input, "%d", &mp[0][0]) != EOF) {
				printf("%d\n", cnt++);
				for (int i = 1;i < 81;i++) {
					fscanf(input, "%d", &mp[i / 9][i % 9]);
				}
				for (int i = 0;i < 9;i++) {
					for (int j = 0;j < 9;j++) {
						mp[i][j]--;
					}
				}
				for (int i = 0;i < 9;i++) {
					if (error_flag) {
						break;
					}
					for (int j = 0;j < 9;j++) {
						if (error_flag) {
							break;
						}
						if (judge_unit(i, j, mp[i][j])) {
							error_flag = 1;
							break;
						}
						visit_row[i][mp[i][j]] = 1;
						visit_col[j][mp[i][j]] = 1;
						visit_squard[i / 3][j / 3][mp[i][j]] = 1;
					}
				}
				memset(visit_col, 0, sizeof(visit_col));
				memset(visit_row, 0, sizeof(visit_row));
				memset(visit_squard, 0, sizeof(visit_squard));
			}
			return error_flag;
		}
	};
}