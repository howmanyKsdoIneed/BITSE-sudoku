#pragma once
#ifndef BITSE_SOLVER
#define BITSE_SOLVER
#include <sal.h>
#include <iostream>
#include "sudoku.h"
#include "defines.h"

class Solver
{
private:
	Sudoku puzzle;

public:

	/// <summary>
	/// ��ʼ���������
	/// �����������������Ϊ���������
	/// </summary>
	Solver(const Sudoku& _puzzle)noexcept :puzzle(_puzzle) {}

	/// <summary>
	/// ��ʼ���������
	/// ��ʱ��������ȫ�յģ�
	/// </summary>
	Solver()noexcept {}

	/// <summary>
	/// ���³�ʼ���������
	/// �����������������Ϊ���������
	/// </summary>
	void Reload(const Sudoku& src);

	/// <summary>
	///	�жϵ�ǰ���������Ƿ�Ϸ�
	/// ʹ���ڲ�Sudoku�����IsValid����
	/// </summary>
	/// <param name="slotOk">ָʾ��λ(����0��λ��)�Ƿ���Ϊ�Ϸ���Ϊtrue��ʾ��Ϊ�Ϸ���</param>
	inline bool IsValid(bool slotOK);

	/// <summary>
	///	�ݹ�س��Խ�һ��������������ʾ��ǰӦ���ȿ��ǵ�λ�á����Ǹ�λ�ò��ǿ�λ������ѡһ����λ����
	/// </summary>
	/// <param name="line">��ǰ��Ҫ��λ���У���0��ʼ</param>
	/// <param name="col">��ǰ��Ҫ��λ���У���0��ʼ</param>
	bool Solve(
		_pos_range_ int line = 0,
		_pos_range_ int col = 0
	);

	friend ostream& operator<<(ostream& os, const Solver& solver);
};

ostream& operator<<(ostream& os, const Solver& solver);

#endif