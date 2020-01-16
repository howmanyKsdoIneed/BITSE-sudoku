#include "sudoku.h"
using namespace std;

/// <summary>
/// ����a��i������(a mod (9-i)!)/(8-i)!��ֵ,����Ӧ�еı���
/// a����һ�еı��룬i����ǰ���ǵ��к�
/// </summary>
/// <param name="topId">��һ�б���</param>
/// <param name="pos">�к�</param>
int GetOffset(_In_range_(0, 40319) int topId, _pos_range_ int pos);


Sudoku::Sudoku()noexcept :board{ {0} } {}

Sudoku::Sudoku(_In_range_(0, 2903039) int id, _ans_range_ int upLeft) : board{ {0} } { Build(id, upLeft); }

void Sudoku::Build(_In_range_(0, 2903039) int id, _ans_range_ int upLeft)
{
	int* builder[9]{ nullptr };
	for (int line = 0; line < 9; line++)
		builder[line] = new int[9];

	if (id < 0 || id>2903039)
		id = 0;
	if (upLeft <= 0 || upLeft > 9)
		upLeft = 1;

	//��ʼ����һ�У��̶���һ�е�һ�е�����
	for (int i = 0; i < 9; i++)
		builder[0][i] = i + 1;
	swap(builder[0][0], builder[0][upLeft - 1]);

	//���ɵ�һ����������
	const int iTopCode = id / 72;//˵���ĵ����վ����ɡ�һ���е�a
	for (int col = 1; col < 8; col++)	//���һ�в��迼��
		swap(builder[0][col], builder[0][col + GetOffset(iTopCode, col)]);

	//���������еĳ�ʼ״̬
	//��������
	for (int col = 0; col < 9; col++)
	{
		builder[1][col] = builder[0][(col + 3) % 9];
		builder[2][col] = builder[0][(col + 6) % 9];
	}
	//ʣ����
	for (int subline = 0; subline < 3; subline++)
	{
		for (int col = 0; col < 9; col++)
		{
			builder[subline + 3][col] = builder[subline][(col + 1) % 9];
			builder[subline + 6][col] = builder[subline][(col + 2) % 9];
		}
	}

	//���������ʣ���е�˳��
	const int topId = (id % 72) / 36;	//�������еı���
	const int midId = (id % 36) / 6;	//4-6�еı���
	const int btmId = id % 6;			//7-9�еı���
	//2-3��
	if (topId != 0)
		swap(builder[1], builder[2]);
	//4-6��
	swap(builder[3], builder[3 + (midId % 3)]);
	swap(builder[4], builder[4 + (midId % 2)]);
	//7-9��
	swap(builder[6], builder[6 + (btmId % 3)]);
	swap(builder[7], builder[7 + (btmId % 2)]);

	for (int line = 0; line < 9; line++)
	{
		for (int col = 0; col < 9; col++)
			At(line, col) = builder[line][col];
		delete[] builder[line];
	}
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

void Sudoku::Print(FILE* outFile)
{
	for (int line = 0; line < 9; line++)
	{
		fprintf_s(
			outFile,
			"%d %d %d %d %d %d %d %d %d\n",
			At(line, 0),
			At(line, 1),
			At(line, 2),
			At(line, 3),
			At(line, 4),
			At(line, 5),
			At(line, 6),
			At(line, 7),
			At(line, 8)
		);
	}
	return;
}

int Sudoku::Read(FILE* inFile)
{
	for (int line = 0; line < 9; line++)
	{
		if (fscanf_s(inFile, "%d%d%d%d%d%d%d%d%d",
			&(At(line, 0)),
			&(At(line, 1)),
			&(At(line, 2)),
			&(At(line, 3)),
			&(At(line, 4)),
			&(At(line, 5)),
			&(At(line, 6)),
			&(At(line, 7)),
			&(At(line, 8))
		) == EOF)
			return EOF;
	}
	return 0;
}

Sudoku& Sudoku::operator=(const Sudoku& src)
{
	for (int line = 0; line < 9; line++)
		for (int col = 0; col < 9; col++)
			board[line][col] = src.board[line][col];
	return *this;
}

bool Sudoku::operator==(const Sudoku& another)
{
	for (int line = 0; line < 9; line++)
		for (int col = 0; col < 9; col++)
			if (board[line][col] != another.board[line][col])
				return false;
	return true;
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
