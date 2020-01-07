#pragma once
#ifndef BITSE_MAIN
#define BITSE_MAIN
#include "defines.h"
#include <fstream>
using namespace std;

/// <summary>
/// 终局生成模块的执行入口
/// </summary>
void CreateEndgame(_In_range_(0, maxCreates) int count);

/// <summary>
/// 解数独模块的执行入口
/// 题目文件须事先准备好
/// <summary>
void Solve(istream& file);

void PrintUsage(ostream& os);


#endif // !BITSE_MAIN
