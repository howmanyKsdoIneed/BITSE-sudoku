//main.cpp
//sudoku.exe 主程序文件
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include "sudoku.h"
#include "solver.h"
using namespace std;

const string strOutFileName("sudoku.txt");
const int maxCreates = 2000010;

void CreateEndgame(_In_range_(0, maxCreates) int count);
void Solve(istream& file);
void PrintUsage(ostream& os);

int main(int argc, char** argv)
{
	if (argc < 3)	//参数个数小于2个，表明调用方式不正确
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
		int iOutCount = atoi(argv[2]);
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
		ifstream fInFile(argv[2]);
		if (fInFile.is_open())
			Solve(fInFile);
		else
		{
			cerr << "未能成功打开输入文件 " << argv[2] << endl;
			return -1;
		}
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
