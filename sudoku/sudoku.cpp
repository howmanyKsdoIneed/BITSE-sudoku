#include "sudoku.h"
using namespace std;

Sudoku::Sudoku() :board{ {0} } {}

bool Sudoku::IsValid(bool slotOk)
{
	//逐行检查
	for (int line = 0; line < 9; line++)
	{
		bool existFlag[10]{ false };
		for (int col = 0; col < 9; col++)
		{
			if (board[line][col] == 0)	//发现空位
			{
				if (slotOk)
					continue;
				else
					return false;
			}
			else
			{
				if (existFlag[board[line][col]])	//该数值已出现
					return false;
				else
					existFlag[board[line][col]] = true;
			}
		}
	}

	//逐列检查
	for (int col = 0; col < 9; col++)
	{
		bool existFlag[10]{ false };
		for (int line = 0; line < 9; line++)
		{
			if (board[line][col] == 0)	//发现空位
				//若不允许空位，逐行检查时已经退出，故此时无需考虑
				continue;
			else
			{
				if (existFlag[board[line][col]])	//该数值已出现
					return false;
				else
					existFlag[board[line][col]] = true;
			}
		}
	}

	//逐九宫格检查
	for(int subL=0;subL<3;subL++)
		for (int subC = 0; subC < 3; subC++)
		{
			bool existFlag[10]{ false };
			for(int line=0;line<3;line++)
				for (int col = 0; col < 3; col++)
				{
					if (board[3 * subL + line][3 * subC + col] == 0)
						continue;
					if (existFlag[board[3 * subL + line][3 * subC + col]])
						return false;
					else
						existFlag[board[3 * subL + line][3 * subC + col]] = true;
				}
		}

	return true;
}

inline int& Sudoku::At(_pos_range_ int line, _pos_range_ int col)
{
	return board[line][col];
}

ostream& operator<<(ostream& os, const Sudoku& sudoku)
{
	for (int line = 0; line < 9; line++)
	{
		os << sudoku.board[line][0];
		for (int col = 1; col < 9; col++)
			os << ' ' << sudoku.board[line][col];
		os << endl;
	}
}

istream& operator>>(istream& s, Sudoku& sudoku)
{
	for (int line = 0; line < 9; line++)
		for (int col = 0; col < 9; col++)
			s >> sudoku.board[line][col];
	return s;
}
