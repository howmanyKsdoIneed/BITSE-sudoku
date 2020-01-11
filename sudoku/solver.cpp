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
	//ȷ�����ε���Ҫ����Ŀ�λ��λ��
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
		//�������˱����ѱ�������������λ�ã�δ�ҵ���λ
		//�������Ϸ�������true
		return IsValid(false);
	}

foundSlot:;

	//ȷ����ǰ��λ�������������
	bool bNumAllowed[10]{ false };
	for (int i = 1; i < 10; i++)
		bNumAllowed[i] = true;
	for (int i = 0; i < 9; i++)	//�к���
	{
		bNumAllowed[puzzle.At(i, col)] = false;
		bNumAllowed[puzzle.At(line, i)] = false;
	}
	const int subBeginL = line - (line % 3);
	const int subBeginC = col - (col % 3);
	for (int subL = 0; subL < 3; subL++)	//�Ź���
		for (int subC = 0; subC < 3; subC++)
			bNumAllowed[puzzle.At(subBeginL + subL, subBeginC + subC)] = false;

	//���µݹ�
	for (int i = 1; i < 10; i++)
	{
		if (bNumAllowed[i] == false)
			continue;
		puzzle.At(line, col) = i;
		if (Solve())	//���µݹ�Ľ���ǵý⣬�ͷ��صý⣬����������״̬����
			return true;
	}

	//���п��ܵ����ֶ��޽⣬��ԭ���̲������޽�
	puzzle.At(line, col) = 0;
	return false;
}
