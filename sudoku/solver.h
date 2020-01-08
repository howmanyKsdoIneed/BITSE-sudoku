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
	/// 初始化解题对象
	/// 拷贝传入的数独，作为将解的谜题
	/// </summary>
	Solver(const Sudoku& _puzzle)noexcept :puzzle(_puzzle) {}

	/// <summary>
	/// 初始化解题对象
	/// 此时的棋盘是全空的！
	/// </summary>
	Solver()noexcept {}

	/// <summary>
	/// 重新初始化解题对象
	/// 拷贝传入的数独，作为将解的谜题
	/// </summary>
	void Reload(const Sudoku& src);

	/// <summary>
	///	判断当前数独棋盘是否合法
	/// 使用内部Sudoku对象的IsValid方法
	/// </summary>
	/// <param name="slotOk">指示空位(填入0的位置)是否视为合法。为true表示视为合法。</param>
	inline bool IsValid(bool slotOK);

	/// <summary>
	///	递归地尝试解一个数独。参数表示当前应首先考虑的位置。若那个位置不是空位，则任选一个空位处理。
	/// </summary>
	/// <param name="line">当前首要空位的行，从0开始</param>
	/// <param name="col">当前首要空位的列，从0开始</param>
	bool Solve(
		_pos_range_ int line = 0,
		_pos_range_ int col = 0
	);

	friend ostream& operator<<(ostream& os, const Solver& solver);
};

ostream& operator<<(ostream& os, const Solver& solver);

#endif