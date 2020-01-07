#pragma once
#ifndef BITSE_DEFINES
#define BITSE_DEFINES
#include <sal.h>
#include <iostream>
#include <string>

//�Ϸ��ĺ�������(0��8)
#define _pos_range_ _In_range_(0, 8)
//����Ϸ���ֵ(0-9, ����λ0)
#define _val_range_ _In_range_(0, 9)
//����Ϸ��Ĵ�(1-9, ������λ0)
#define _ans_range_ _In_range_(1, 9)

const std::string strOutFileName("sudoku.txt");
const int maxCreates = 2000010;
const int upLeft = 3;

#endif // !BITSE_DEFINES
