#include "solver.h"

void Solver::Reload(const Sudoku& src)
{
	puzzle = src;
	return;
}

inline bool Solver::IsValid(bool slotOK) { return puzzle.IsValid(slotOK); }

ostream& operator<<(ostream& os, const Solver& solver)
{
	return os << solver.puzzle;
}

bool Solver::Solve(_pos_range_ int line, _pos_range_ int col)
{
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
		//若数独合法，返回true
		return IsValid(false);
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
