#include "solver.h"
#include <cstring>
#include <vector>

void Solver::Reload(const Sudoku& src)
{
	puzzle = src;

	//初始化可以填入的数字表
	memset(canFit, true, sizeof(canFit));
	for (int line = 0; line < 9; line++)
	{
		for (int col = 0; col < 9; col++)
		{
			int num = puzzle.At(line, col);
			if (num != 0)
			{
				for (int i = 0; i < 9; i++)
				{
					canFit[line][i][num] = false;
					canFit[i][col][num] = false;
				}
				for (int subL = 0; subL < 3; subL++)
					for (int subC = 0; subC < 3; subC++)
						canFit[line / 3 + subL][col / 3 + subC][num] = false;
			}
		}
	}

	//初始化可以填入的数字个数表
	for (int line = 0; line < 9; line++)
	{
		for (int col = 0; col < 9; col++)
		{
			fitCount[line][col] = 0;
			for (int num = 1; num < 10; num++)
				if (canFit[line][col][num])
					fitCount[line][col]++;
		}
	}

	return;
}

ostream& operator<<(ostream& os, const Solver& solver)
{
	return os << solver.puzzle;
}

bool Solver::Solve(_pos_range_ int line, _pos_range_ int col)
{
	//搜索已经无法填数的空位，若找到直接返回无解
	for (int line = 0; line < 9; line++)
		for (int col = 0; col < 9; col++)
			if (puzzle.At(line, col) == 0 && fitCount[line][col] == 0)
				return false;

	//记录填数操作
	vector<int> fillL, fillC;
	//记录可填数字更改
	vector<int> prefitL, prefitC, prefitNum;

	//搜索只有一个数可以填入的空位
	for(int line=0;line<9;line++)
		for(int col=0;col<9;col++)
			if (puzzle.At(line, col) == 0 && fitCount[line][col] == 1)
			{
				for (int num = 1; num < 10; num++)
				{
					if (canFit[line][col][num])
					{
						//填入数字
						puzzle.At(line, col) = num;
						fillL.push_back(line);
						fillC.push_back(col);
						//维护可填数字列表
						for (int i = 0; i < 9; i++)
						{
							if (canFit[i][col][num])
							{
								canFit[i][col][num] = false;
								fitCount[i][col]--;
								prefitL.push_back(i);
								prefitC.push_back(col);
								prefitNum.push_back(num);
							}
							if (canFit[line][i][num])
							{
								canFit[line][i][num] = false;
								fitCount[line][i]--;
								prefitL.push_back(line);
								prefitC.push_back(i);
								prefitNum.push_back(num);
							}
						}
						for(int subL=0;subL<3;subL++)
							for (int subC = 0; subC < 3; subC++)
								if (canFit[line / 3 + subL][col / 3 + subC][num])
								{
									canFit[line / 3 + subL][col / 3 + subC][num] = false;
									fitCount[line / 3 + subL][col / 3 + subC]--;
									prefitL.push_back(line / 3 + subL);
									prefitC.push_back(col / 3 + subC);
									prefitNum.push_back(num);
								}

						break;
					}
				}
			}

	//确定本次调用要处理的空位的位置
	if (line < 0 || line>8)
		line = 0;
	if (col < 0 || col>8)
		col = 0;
	if (puzzle.At(line, col) != 0)
	{
		for (line = 0; line < 9; line++)
			for (col = 0; col < 9; col++)
				if (puzzle.At(line, col) == 0)
					goto foundSlot;
		//运行至此表明已遍历棋盘上所有位置，未找到空位
		//若数独合法，表明得解，返回true
		//否则，还原棋盘状态，返回false
		if (IsValid(false))
			return true;
		else
		{
			for (int i = 0; i < fillL.size(); i++)
				puzzle.At(fillL[i], fillC[i]) = 0;
			for (int i = 0; i < prefitL.size(); i++)
			{
				canFit[prefitL[i]][prefitC[i]][prefitNum[i]] = true;
				fitCount[prefitL[i]][prefitC[i]]++;
			}
			return false;
		}
	}

foundSlot:;

	//确定当前空位可以填入的数字
	bool bNumAllowed[10]{ false };
	for (int i = 1; i < 10; i++)
		bNumAllowed[i] = true;
	for (int i = 0; i < 9; i++)	//行和列
	{
		bNumAllowed[puzzle.At(i, col)] = false;
		bNumAllowed[puzzle.At(line, i)] = false;
	}
	const int subBeginL = line - (line % 3);
	const int subBeginC = col - (col % 3);
	for (int subL = 0; subL < 3; subL++)	//九宫格
		for (int subC = 0; subC < 3; subC++)
			bNumAllowed[puzzle.At(subBeginL + subL, subBeginC + subC)] = false;

	//向下递归
	for (int i = 1; i < 10; i++)
	{
		if (bNumAllowed[i] == false)
			continue;
		puzzle.At(line, col) = i;
		if (Solve())	//向下递归的结果是得解，就返回得解，并保持棋盘状态不变
			return true;
	}

	//所有可能的数字都无解，还原棋盘并返回无解
	puzzle.At(line, col) = 0;
	return false;
}
