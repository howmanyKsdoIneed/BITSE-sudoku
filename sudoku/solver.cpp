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
	for (int _line = 0; _line < 9; _line++)
		for (int _col = 0; _col < 9; _col++)
			if (puzzle.At(_line, _col) == 0 && fitCount[_line][_col] == 1)
			{
				for (int num = 1; num < 10; num++)
				{
					if (canFit[_line][_col][num])
					{
						//填入数字
						puzzle.At(_line, _col) = num;
						fillL.push_back(_line);
						fillC.push_back(_col);
						//维护可填数字列表
						for (int i = 0; i < 9; i++)
						{
							if (canFit[i][_col][num])
							{
								canFit[i][_col][num] = false;
								fitCount[i][_col]--;
								prefitL.push_back(i);
								prefitC.push_back(_col);
								prefitNum.push_back(num);
							}
							if (canFit[_line][i][num])
							{
								canFit[_line][i][num] = false;
								fitCount[_line][i]--;
								prefitL.push_back(_line);
								prefitC.push_back(i);
								prefitNum.push_back(num);
							}
						}
						for(int subL=0;subL<3;subL++)
							for (int subC = 0; subC < 3; subC++)
								if (canFit[_line / 3 + subL][_col / 3 + subC][num])
								{
									canFit[_line / 3 + subL][_col / 3 + subC][num] = false;
									fitCount[_line / 3 + subL][_col / 3 + subC]--;
									prefitL.push_back(_line / 3 + subL);
									prefitC.push_back(_col / 3 + subC);
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
	int leastFits = 10;
	for (int tgtL = 0; tgtL < 9; tgtL++)
	{
		for (int tgtC = 0; tgtC < 9; tgtC++)
		{
			if (puzzle.At(tgtL, tgtC) == 0 && fitCount[tgtL][tgtC] < leastFits)
			{
				line = tgtL;
				col = tgtC;
			}
		}
	}
	if (puzzle.At(line, col) != 0)	//已遍历棋盘上所有位置，未找到空位
	{
		if (IsValid(false))	//若数独合法，表明得解，返回true
			return true;
		else				//否则，还原棋盘状态，返回false
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

	//向下递归
	vector<int> fitL, fitC;	//记录可填数字更改
	for (int num = 1; num < 10; num++)
	{
		if (!canFit[line][col][num])
			continue;
		//填入数字
		puzzle.At(line, col) = num;
		//维护可填入数字表
		for (int i = 0; i < 9; i++)
		{
			if (canFit[i][col][num])
			{
				canFit[i][col][num] = false;
				fitCount[i][col]--;
				fitL.push_back(i);
				fitC.push_back(col);
			}
			if (canFit[line][i][num])
			{
				canFit[line][i][num] = false;
				fitCount[line][i]--;
				fitL.push_back(line);
				fitC.push_back(i);
			}
		}
		for (int subL = 0; subL < 3; subL++)
		{
			for (int subC = 0; subC < 3; subC++)
			{
				if (canFit[line / 3 + subL][col / 3 + subC][num])
				{
					canFit[line / 3 + subL][col / 3 + subC][num] = false;
					fitCount[line / 3 + subL][col / 3 + subC]--;
					fitL.push_back(line / 3 + subL);
					fitC.push_back(col / 3 + subC);
				}
			}
		}

		if (Solve())	//向下递归的结果是得解，就返回得解，并保持棋盘状态不变
			return true;
		else			//若没有得解，就还原可填入数字表
		{
			for (int i = 0; i < fitL.size(); i++)
			{
				canFit[fitL[i]][fitC[i]][num] = true;
				fitCount[fitL[i]][fitC[i]]++;
			}
			fitL.clear();
			fitC.clear();
		}
	}

	//所有可能的数字都无解，还原棋盘并返回无解
	puzzle.At(line, col) = 0;
	return false;
}
