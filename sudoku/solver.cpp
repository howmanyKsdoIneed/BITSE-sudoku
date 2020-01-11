#include "solver.h"
#include <cstring>
#include <vector>

void Solver::Reload(const Sudoku& src)
{
	puzzle = src;

	//��ʼ��������������ֱ�
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

	//��ʼ��������������ָ�����
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
	//�����Ѿ��޷������Ŀ�λ�����ҵ�ֱ�ӷ����޽�
	for (int line = 0; line < 9; line++)
		for (int col = 0; col < 9; col++)
			if (puzzle.At(line, col) == 0 && fitCount[line][col] == 0)
				return false;

	//��¼��������
	vector<int> fillL, fillC;
	//��¼�������ָ���
	vector<int> prefitL, prefitC, prefitNum;

	//����ֻ��һ������������Ŀ�λ
	for(int line=0;line<9;line++)
		for(int col=0;col<9;col++)
			if (puzzle.At(line, col) == 0 && fitCount[line][col] == 1)
			{
				for (int num = 1; num < 10; num++)
				{
					if (canFit[line][col][num])
					{
						//��������
						puzzle.At(line, col) = num;
						fillL.push_back(line);
						fillC.push_back(col);
						//ά�����������б�
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
		//�������Ϸ��������ý⣬����true
		//���򣬻�ԭ����״̬������false
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
