#include "sudoku.h"
using namespace std;

Sudoku::Sudoku() :board{ {0} } {}

bool Sudoku::IsValid(bool slotOk)
{
	//���м��
	for (int line = 0; line < 9; line++)
	{
		bool existFlag[10]{ false };
		for (int col = 0; col < 9; col++)
		{
			if (board[line][col] == 0)	//���ֿ�λ
			{
				if (slotOk)
					continue;
				else
					return false;
			}
			else
			{
				if (existFlag[board[line][col]])	//����ֵ�ѳ���
					return false;
				else
					existFlag[board[line][col]] = true;
			}
		}
	}

	//���м��
	for (int col = 0; col < 9; col++)
	{
		bool existFlag[10]{ false };
		for (int line = 0; line < 9; line++)
		{
			if (board[line][col] == 0)	//���ֿ�λ
				//���������λ�����м��ʱ�Ѿ��˳����ʴ�ʱ���迼��
				continue;
			else
			{
				if (existFlag[board[line][col]])	//����ֵ�ѳ���
					return false;
				else
					existFlag[board[line][col]] = true;
			}
		}
	}

	//��Ź�����
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
