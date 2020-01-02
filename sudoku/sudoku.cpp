#include "sudoku.h"
using namespace std;

/// <summary>
/// ����a��i������(a mod (9-i)!)/(8-i)!��ֵ,����Ӧ�еı���
/// a����һ�еı��룬i����ǰ���ǵ��к�
/// </summary>
/// <param name="topId">��һ�б���</param>
/// <param name="pos">�к�</param>
int GetOffset(_In_range_(0, 40319) int topId, _pos_range_ int pos);

Sudoku::Sudoku() :board{ {0} } {}

Sudoku::Sudoku(_In_range_(0, 2903039) int id, _ans_range_ int upLeft) : board{ {0} }
{
	//��ʼ����һ�У��̶���һ�е�һ�е�����
	for (int i = 0; i < 9; i++)
		board[0][i] = i + 1;
	swap(board[0][0], board[0][upLeft - 1]);

	//���ɵ�һ����������
	int iTopCode = id / 72;//˵���ĵ����վ����ɡ�һ���е�a
	for (int col = 1; col < 8; col++)	//���һ�в��迼��
		swap(board[0][col], board[0][col + GetOffset(iTopCode, col)]);

	//���������еĳ�ʼ״̬
	//��������
	for (int col = 0; col < 9; col++)
	{
		board[1][col] = board[0][(col + 3) % 9];
		board[2][col] = board[0][(col + 6) % 9];
	}
	//ʣ����
	for (int subline = 0; subline < 3; subline++)
	{
		for (int col = 0; col < 9; col++)
		{
			board[subline + 3][col] = board[subline][(col + 1) % 9];
			board[subline + 6][col] = board[subline][(col + 2) % 9];
		}
	}

	//���������ʣ���е�˳��
	int topId = (id % 72) / 36;	//�������еı���
	int midId = (id % 36) / 6;	//4-6�еı���
	int btmId = id % 6;			//7-9�еı���
	//2-3��
	if (topId != 0)
		SwapLine(1, 2);
	//4-6��
	SwapLine(3, 3 + (midId % 3));
	SwapLine(4, 4 + (midId % 2));
	//7-9��
	SwapLine(6, 6 + (btmId % 3));
	SwapLine(7, 7 + (btmId % 2));
}

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
