//main.cpp
//sudoku.exe �������ļ�
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
/// ����ִ�����
/// �������������Ȼ�������Ӧ��ģ��ʵ��ִ��
/// </summary>
int main(int argc,_Notnull_ const char** argv)
{
	if (argc < 3 || argv == nullptr)	//��������С��2�����������÷�ʽ����ȷ
	{
		PrintUsage(cerr);
		return 0;
	}
	if (argv[1][0] != '-')	//��һ������Ӧ��-c��-s
	{
		PrintUsage(cerr);
		return -1;
	}

	if (argv[1][1] == 'c')
	{
		const int iOutCount = atoi(argv[2]);
		if (iOutCount <= 0)
		{
			cerr << "����δ�ܽ��ڶ�������ʶ��Ϊ������" << endl;
			PrintUsage(cerr);
			return -1;
		}
		else if (iOutCount >= maxCreates)
		{
			cerr << "����Ҫ���ɵ������վ�̫��" << endl;
			cerr << "�����վֵĸ�����Ӧ����2,000,000����" << endl;
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
			cerr << "δ�ܳɹ��������ļ� " << argv[2] << endl;
			return -1;
		}
		else
			Solve(fInFile);
	}
	else
	{
		cerr << "����ѡ��δ���塣����ѡ��: -c, -s" << endl;
		PrintUsage(cerr);
		return -1;
	}

	return 0;
}

void PrintUsage(ostream& os)
{
	os << "�÷�: " << endl;
	os << "���������վ�: sudoku.exe -c ��Ŀ" << endl;
	os << "�������: sudoku.exe -s ��Ŀ�ļ���" << endl;
}

void CreateEndgame(_In_range_(0, maxCreates) int count)
{
	FILE* fOutFile = nullptr;
	errno_t err = fopen_s(&fOutFile, strOutFileName.c_str(), "w");
	if (err)
	{
		cerr << "�����޷��򿪽������ļ�" << strOutFileName << endl;
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
		cerr << "�����޷��򿪽������ļ�" << strOutFileName << endl;
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
		if (solver.Solve())	//�������ɹ�
			solver.Print(fOutFile);
		else
			fprintf_s(fOutFile, "����#%d �޽⡣\n", count);
		if (count % 10000 == 0)
			cout << "����#" << count << endl;
		count++;
	}
	return;
}
