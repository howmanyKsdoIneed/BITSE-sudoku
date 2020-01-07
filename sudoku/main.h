#pragma once
#ifndef BITSE_MAIN
#define BITSE_MAIN
#include "defines.h"
#include <fstream>
using namespace std;

/// <summary>
/// �վ�����ģ���ִ�����
/// </summary>
void CreateEndgame(_In_range_(0, maxCreates) int count);

/// <summary>
/// ������ģ���ִ�����
/// ��Ŀ�ļ�������׼����
/// <summary>
void Solve(istream& file);

void PrintUsage(ostream& os);


#endif // !BITSE_MAIN
