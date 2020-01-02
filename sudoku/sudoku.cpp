#include "sudoku.h"
using namespace std;

/// <summary>
/// 输入a和i，计算(a mod (9-i)!)/(8-i)!的值,即对应列的编码
/// a即第一行的编码，i即当前考虑的列号
/// </summary>
/// <param name="topId">第一行编码</param>
/// <param name="pos">列号</param>
int GetOffset(_In_range_(0, 40319) int topId, _pos_range_ int pos);

Sudoku::Sudoku() :board{ {0} } {}

Sudoku::Sudoku(_In_range_(0, 2903039) int id, _ans_range_ int upLeft) : board{ {0} }
{
	//初始化第一行，固定第一行第一列的数字
	for (int i = 0; i < 9; i++)
		board[0][i] = i + 1;
	swap(board[0][0], board[0][upLeft - 1]);

	//生成第一行其他部分
	int iTopCode = id / 72;//说明文档“终局生成”一节中的a
	for (int col = 1; col < 8; col++)	//最后一列不需考虑
		swap(board[0][col], board[0][col + GetOffset(iTopCode, col)]);

	//生成其余行的初始状态
	//二、三行
	for (int col = 0; col < 9; col++)
	{
		board[1][col] = board[0][(col + 3) % 9];
		board[2][col] = board[0][(col + 6) % 9];
	}
	//剩余行
	for (int subline = 0; subline < 3; subline++)
	{
		for (int col = 0; col < 9; col++)
		{
			board[subline + 3][col] = board[subline][(col + 1) % 9];
			board[subline + 6][col] = board[subline][(col + 2) % 9];
		}
	}

	//按编码调换剩余行的顺序
	int topId = (id % 72) / 36;	//二、三行的编码
	int midId = (id % 36) / 6;	//4-6行的编码
	int btmId = id % 6;			//7-9行的编码
	//2-3行
	if (topId != 0)
		SwapLine(1, 2);
	//4-6行
	SwapLine(3, 3 + (midId % 3));
	SwapLine(4, 4 + (midId % 2));
	//7-9行
	SwapLine(6, 6 + (btmId % 3));
	SwapLine(7, 7 + (btmId % 2));
}

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
	return os;
}

istream& operator>>(istream& s, Sudoku& sudoku)
{
	for (int line = 0; line < 9; line++)
		for (int col = 0; col < 9; col++)
			s >> sudoku.board[line][col];
	return s;
}

void Sudoku::SwapLine(_pos_range_ int lineA, _pos_range_ int lineB)
{
	if (lineA < 0 || lineA>8)
		return;
	if (lineB < 0 || lineB>8)
		return;
	if (lineA == lineB)
		return;

	for (int col = 0; col < 9; col++)
		swap(board[lineA][col], board[lineB][col]);
}

int GetOffset(_In_range_(0, 40319) int topId, _pos_range_ int pos)
{
	int modulus = 40320;	//(9-pos)!
	int div = 1;			//(8-pos)!

	int i = 1;
	for (; i <= 8 - pos; i++)
		div *= i;
	modulus = div * i;
	return (topId % modulus) / div;
}
