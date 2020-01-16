//main.cpp
//sudoku.exe 主程序文件
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include "sudoku.h"
#include "solver.h"
#include "main.h"
using namespace std;

const string strOutFileName("sudoku.txt");
constexpr int maxCreates = 2000010;
constexpr int upLeft = 3;

/// <summary>
/// 程序执行入口
/// 任务分析参数，然后调用相应的模块实际执行
/// </summary>
int main(int argc,_Notnull_ const char** argv)
{
	if (argc < 3 || argv == nullptr)	//参数个数小于2个，表明调用方式不正确
	{
		PrintUsage(cerr);
		return 0;
	}
	if (argv[1][0] != '-')	//第一个参数应是-c或-s
	{
		PrintUsage(cerr);
		return -1;
	}

	if (argv[1][1] == 'c')
	{
		const int iOutCount = atoi(argv[2]);
		if (iOutCount <= 0)
		{
			cerr << "错误：未能将第二个参数识别为正整数" << endl;
			PrintUsage(cerr);
			return -1;
		}
		else if (iOutCount >= maxCreates)
		{
			cerr << "错误：要生成的数独终局太多" << endl;
			cerr << "生成终局的个数不应多于2,000,000个。" << endl;
			return -1;
		}
		else
			CreateEndgame(iOutCount);
	}
	else if (argv[1][1] == 's')
	{
		FILE* fInFile = nullptr;
		errno_t err = fopen_s(&fInFile, argv[2], "r");
		if (err)
		{
			cerr << "未能成功打开输入文件 " << argv[2] << endl;
			return -1;
		}
		else
			Solve(fInFile);
	}
	else
	{
		cerr << "错误：选项未定义。可用选项: -c, -s" << endl;
		PrintUsage(cerr);
		return -1;
	}

	return 0;
}

void PrintUsage(ostream& os)
{
	os << "用法: " << endl;
	os << "生成数独终局: sudoku.exe -c 数目" << endl;
	os << "求解数独: sudoku.exe -s 题目文件名" << endl;
}

void CreateEndgame(_In_range_(0, maxCreates) int count)
{
	FILE* fOutFile = nullptr;
	errno_t err = fopen_s(&fOutFile, strOutFileName.c_str(), "w");
	if (err)
	{
		cerr << "错误：无法打开结果输出文件" << strOutFileName << endl;
		return;
	}
	if (fOutFile != nullptr)
	{
		Sudoku endGame;
		for (count--; count >= 0; count--)
		{
			endGame.Build(count, upLeft);
			endGame.Print(fOutFile);
			if (count > 0)
				fprintf_s(fOutFile, "\n");
		}
		fclose(fOutFile);
	}
	return;
}

void Solve(FILE* file)
{
	FILE* fOutFile = nullptr;
	errno_t err = fopen_s(&fOutFile, strOutFileName.c_str(), "w");
	if (err || fOutFile == nullptr)
	{
		cerr << "错误：无法打开结果输出文件" << strOutFileName << endl;
		return;
	}

	Sudoku puzzle;
	Solver solver;
	int count = 1;
	while (true)
	{
		if (puzzle.Read(file) == EOF)
			break;
		solver.Reload(puzzle);
		if (count != 1)
			fputc('\n', fOutFile);
		if (solver.Solve())	//解数独成功
			solver.Print(fOutFile);
		else
			fprintf_s(fOutFile, "谜题#%d 无解。\n", count);
		if (count % 10000 == 0)
			cout << "谜题#" << count << endl;
		count++;
	}
	return;
}
