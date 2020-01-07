#pragma once
#ifndef BITSE_DEFINES
#define BITSE_DEFINES
#include <sal.h>
#include <iostream>
#include <string>

//合法的横纵坐标(0到8)
#define _pos_range_ _In_range_(0, 8)
//格里合法的值(0-9, 含空位0)
#define _val_range_ _In_range_(0, 9)
//格里合法的答案(1-9, 不含空位0)
#define _ans_range_ _In_range_(1, 9)

const std::string strOutFileName("sudoku.txt");
const int maxCreates = 2000010;
const int upLeft = 3;

#endif // !BITSE_DEFINES
