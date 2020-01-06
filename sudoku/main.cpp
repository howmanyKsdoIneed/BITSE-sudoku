//main.cpp
//sudoku.exe �������ļ�
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
	if (argc < 3)	//��������С��2�����������÷�ʽ����ȷ
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
		int iOutCount = atoi(argv[2]);
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
		ifstream fInFile(argv[2]);
		if (fInFile.is_open())
			Solve(fInFile);
		else
		{
			cerr << "δ�ܳɹ��������ļ� " << argv[2] << endl;
			return -1;
		}
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
