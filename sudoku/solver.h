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
	inline Solver(const Sudoku& _puzzle)noexcept { Reload(_puzzle); }

	/// <summary>
	/// ��ʼ���������
	/// ��ʱ��������ȫ�յģ�
	/// </summary>
	inline Solver()noexcept { Reload(Sudoku()); }

	/// <summary>
	/// ���³�ʼ���������
	/// �����������������Ϊ���������
	/// </summary>
	inline void Reload(const Sudoku& src) { puzzle = src; }

	/// <summary>
	///	�жϵ�ǰ���������Ƿ�Ϸ�
	/// ʹ���ڲ�Sudoku�����IsValid����
	/// </summary>
	/// <param name="slotOk">ָʾ��λ(����0��λ��)�Ƿ���Ϊ�Ϸ���Ϊtrue��ʾ��Ϊ�Ϸ���</param>
	inline bool IsValid(bool slotOK) { return puzzle.IsValid(slotOK); }

	/// <summary>
	///	�ݹ�س��Խ�һ��������������ʾ��ǰӦ���ȿ��ǵ�λ�á����Ǹ�λ�ò��ǿ�λ������ѡһ����λ����
	/// </summary>
	/// <param name="line">��ǰ��Ҫ��λ���У���0��ʼ</param>
	/// <param name="col">��ǰ��Ҫ��λ���У���0��ʼ</param>
	bool Solve(
		_pos_range_ int line = 0,
		_pos_range_ int col = 0
	);

	inline void Print(FILE* fOutFile) { puzzle.Print(fOutFile); }

	friend ostream& operator<<(ostream& os, const Solver& solver);
};

inline ostream& operator<<(ostream& os, const Solver& solver) { return os << solver.puzzle; }

#endif